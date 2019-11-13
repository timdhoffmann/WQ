// Fill out your copyright notice in the Description page of Project Settings.

#include "MagnetPower.h"
#include "WQCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Props/Props.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Camera/CameraComponent.h"
#include "ConstructorHelpers.h"
#include "MagnetIndicator.h"

/** Sets default values for this component's properties */
UMagnetPower::UMagnetPower()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features 
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default values
	MagnetRange = 500.0f;
	SphereRadius = 20.0f;
	MagnetRadius = 60.0f;
	MagnetForce = 100000.0f;
	bIsTargettingActivated = false;
	PropulsionForce = 500000.0f;
	MagnetizationRadiusCoeff = 0.8f;
	Identifier = 0;

	/// Grabs the references of the BP, here so that we counter the infamous UE4 bug where the references are lost upon reopening
	static ConstructorHelpers::FObjectFinder<UClass> MagnetIndicatorClassFinder(TEXT("Class'/Game/Blueprints/Powers/BP_MagnetIndicator.BP_MagnetIndicator_C'"));
	if (MagnetIndicatorClassFinder.Object)
	{
		MagnetIndicatorBP = MagnetIndicatorClassFinder.Object;
	}
}


/** Called when the game starts */
void UMagnetPower::BeginPlay()
{
	Super::BeginPlay();

	// Create the sweep parameters 
	Sphere = FCollisionShape::MakeSphere(SphereRadius);
	BiggerSphere = FCollisionShape::MakeSphere(MagnetRadius);
	SweepParams = FCollisionQueryParams();
	SweepParams.AddIgnoredActor(Character); // Ignore the character in the sweep

	// Spawn the indicator
	if (MagnetIndicatorBP)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			MagnetIndicator = World->SpawnActor<AMagnetIndicator>(MagnetIndicatorBP, Character->GetActorLocation(), Character->GetActorRotation());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MagnetPower: MagnetIndicatorBP not set!"));
	}
}

/** Called every frame */
void UMagnetPower::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsTargettingActivated)
	{
		UpdateMagnet();
	}
}

/** Behaviour when the power is pressed */
void UMagnetPower::PowerPressed()
{
	// Activate the power only if it's not already activated or if the objects are not being dragged towards the player
	if (!bIsTargettingActivated)
	{
		bIsTargettingActivated = true;
		if (MagnetIndicator)
			MagnetIndicator->SetActorActive(true);
	}
}

/** Behaviour when the power is released */
void UMagnetPower::PowerReleased()
{
	// Deactivate the power only if it's already activated
	if (bIsTargettingActivated)
	{
		bIsTargettingActivated = false;

		Character->ClearAllPhysicHandle();

		for (AProps* Prop : MagnetizedProps)
		{
			if (Prop != nullptr)
			{
				Prop->FlyStop();
				Prop->Propulse(Character->GetFirstPersonCameraComponent()->GetForwardVector(), PropulsionForce);
				Prop->SetMaterial(Mat1);
			}
		}
		MagnetizedProps.Empty();
		if(MagnetIndicator)
			MagnetIndicator->SetActorActive(false);
	}
}

/** Update the magnet (target, objects in it...) */
void UMagnetPower::UpdateMagnet()
{
	// Update the sphere sweep, not taking into account the props
	UWorld* const World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("MagnetPower: World not found!"));
	}
	FHitResult Hit(1.0f);
	FVector Start = UGameplayStatics::GetPlayerCameraManager(World, 0)->GetCameraLocation() + 10.0f * UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector();
	FVector End = Start + MagnetRange * UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector();	
	World->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, Sphere, SweepParams);
	FVector FinalLocation = Hit.bBlockingHit ? Hit.Location : Hit.TraceEnd;

	// Update the indicator location and rotation
	if (MagnetIndicator)
	{
		MagnetIndicator->SetActorLocation(FinalLocation);
		FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(FinalLocation, Character->GetActorLocation());
		MagnetIndicator->SetActorRotation(LookAtRotator);
	}

	// Update the physic handles location
	for (UPhysicsHandleComponent* PH : Character->GetPhysicHandles())
	{
		PH->SetTargetLocation(FinalLocation);
	}
	DrawDebugSphere(World, FinalLocation, SphereRadius, 32, FColor::White);

	// Find all props in a new sweep based on the hit of the previous one
	TArray<FOverlapResult> OutProps;
	if (World->OverlapMultiByChannel(OutProps, FinalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, BiggerSphere, SweepParams))
	{
		for (FOverlapResult Res : OutProps)
		{
			AProps* Prop = Cast<AProps>(Res.Actor);
			if (Prop != nullptr && !MagnetizedProps.Contains(Prop))
			{
				TArray<UPrimitiveComponent*> PrimComps;
				Prop->GetComponents<UPrimitiveComponent>(PrimComps);
				UPhysicsHandleComponent* PH = Character->GetUnusedPhysicHandle();
				PH->SetTargetLocation(FinalLocation); // Make sure the location is set correctly in case this is a new physic handle
				FVector Direction = FinalLocation - Prop->GetActorLocation();
				FVector GrabLocation = Prop->GetActorLocation() + Direction * MagnetizationRadiusCoeff;
				PH->GrabComponentAtLocation(PrimComps[0], FName("", MagnetizedProps.Num()), GrabLocation);
				Prop->FlyTowards(FinalLocation, MagnetForce);
				MagnetizedProps.Add(Prop);
				Prop->SetMaterial(Mat2);
			}
		}
	}
}

