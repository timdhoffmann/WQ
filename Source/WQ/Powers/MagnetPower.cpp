// Fill out your copyright notice in the Description page of Project Settings.

#include "MagnetPower.h"
#include "WQCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Props/Props.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
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
}


// Called when the game starts
void UMagnetPower::BeginPlay()
{
	Super::BeginPlay();

	// Create the sweep parameters
	Sphere = FCollisionShape::MakeSphere(SphereRadius);
	BiggerSphere = FCollisionShape::MakeSphere(MagnetRadius);
	SweepParams = FCollisionQueryParams();
	SweepParams.AddIgnoredActor(Character); // Ignore the character in the sweep
}

// Called every frame
void UMagnetPower::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsTargettingActivated)
	{
		UpdateMagnet();
	}
}

// Behaviour when the power is pressed
void UMagnetPower::PowerPressed()
{
	// Activate the power only if it's not already activated or if the objects are not being dragged towards the player
	if (!bIsTargettingActivated)
	{
		bIsTargettingActivated = true;
	}
}

// Behaviour when the power is released
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
	}
}

// Update the magnet (target, objects in it...)
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
	World->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, BiggerSphere, SweepParams);
	FVector FinalLocation = Hit.bBlockingHit ? Hit.Location : Hit.TraceEnd;
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

