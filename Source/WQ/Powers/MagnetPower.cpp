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
#include "Managers/WQGameInstance.h"
#include "Managers/AudioManager.h"
#include "Math/UnrealMathUtility.h"

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
	PropulsionForce = 500000.0f;
	MagnetizationRadiusCoeff = 0.8f;
	Identifier = 0;
	MinMagnetizedSpeed = 1000.0f;
	MaxMagnetizedSpeed = 5000.0f;
	PreviousSlope = 0.0f;
	PreviousRTPCValue = 0.0f;
	MinPropsAmountToSummon = 4;
	GlowMultiplier = 10.0f;
	DeniedSummonColor = FLinearColor::Red;
	DeniedSummonGlowDuration = 0.3f;
	DeniedSummonGlowMultiplier = 200.0f;
	SummonCheckboxExtent = FVector(50.0f, 50.0f, 20.0f);

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
	SummonCheckbox = FCollisionShape::MakeBox(SummonCheckboxExtent * 0.5f);
	//SummonCheckbox = FCollisionShape::MakeCapsule(100.0f, 50.0f);
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

	if (MagnetState != EMagnetEnum::ME_None)
	{
		UpdateMagnet();

		UpdateMagnetRTPC();

		if (MagnetState == EMagnetEnum::ME_Summoning)
		{
			UpdateSummonTargetting();
		}
	}
}

/** Behaviour when the power is activated */
void UMagnetPower::SetPowerActive(bool bState)
{
	if (bState)
	{
		// Subscribe to the correct events
		Character->OnPowerPressed().AddUFunction(this, TEXT("PowerPressed"));
		Character->OnPowerReleased().AddUFunction(this, TEXT("PowerReleased"));
		Character->OnSummonPressed().AddUFunction(this, TEXT("SummonPressed"));
		Character->OnSummonReleased().AddUFunction(this, TEXT("SummonReleased"));
		MagnetState = EMagnetEnum::ME_None;
	}
	else
	{
		// Unsubscribe
		Character->OnPowerPressed().RemoveAll(this);
		Character->OnPowerReleased().RemoveAll(this);
		Character->OnSummonPressed().RemoveAll(this);
		Character->OnSummonReleased().RemoveAll(this);
		MagnetState = EMagnetEnum::ME_None;
	}
}

/** Behaviour when the power is pressed */
void UMagnetPower::PowerPressed()
{
	// Activate the power only if it's not already activated
	if (MagnetState == EMagnetEnum::ME_None)
	{
		MagnetState = EMagnetEnum::ME_Targetting;
		if (MagnetIndicator)
		{
			MagnetIndicator->SetActorActive(true);
		}
	}
}

/** Behaviour when the power is released */
void UMagnetPower::PowerReleased()
{
	// Deactivate the power only if it's already activated
	if (MagnetState != EMagnetEnum::ME_None)
	{
		MagnetState = EMagnetEnum::ME_None;

		Character->ClearAllPhysicHandle();

		for (AProps* Prop : MagnetizedProps)
		{
			if (IsValid(Prop))
			{
				Prop->FlyStop();
				//Prop->Propulse(Character->GetFirstPersonCameraComponent()->GetForwardVector(), PropulsionForce);
				
				// Make the prop unglow
				Prop->SetGlow(0.0f);

				// Stop the ambiance sound
				if (IsValid(GameInstance))
				{
					GameInstance->AudioManager()->SetPropMagnetizedAmbiance(false, Prop);
				}
			}
		}
		MagnetizedProps.Empty();
		if (MagnetIndicator)
		{
			MagnetIndicator->SetActorActive(false);
		}
	}
}

/** Behaviour when the summon action is pressed */
void UMagnetPower::SummonPressed()
{
	// Only launch the summoning if we have enough props
	if (MagnetState == EMagnetEnum::ME_Targetting && MagnetizedProps.Num() >= MinPropsAmountToSummon)
	{
		MagnetState = EMagnetEnum::ME_Summoning;
	}
	// Otherwise, make the objects glow red
	else
	{
		for (AProps* Prop : MagnetizedProps)
		{
			if (IsValid(Prop))
			{
				Prop->SetGlow(DeniedSummonGlowMultiplier, DeniedSummonGlowDuration, DeniedSummonColor, true);
			}
		}
	}
}

/** Behaviour when the summon action is released */
void UMagnetPower::SummonReleased()
{
	if (MagnetState == EMagnetEnum::ME_Summoning)
	{
		// Check if we can summon
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

				// Make the prop glow
				Prop->SetGlow(GlowMultiplier);

				// Play the required sound
				if (IsValid(GameInstance))
				{
					GameInstance->AudioManager()->PlayPropMagnetized(Prop);
					GameInstance->AudioManager()->SetPropMagnetizedAmbiance(true, Prop);
				}
			}
		}
	}
}

/** Update the audio RTPC of the magnetized props */
void UMagnetPower::UpdateMagnetRTPC()
{
	if (IsValid((GameInstance)))
	{
		for (AProps* Prop : MagnetizedProps)
		{
			// Calculate the new RTPC value and slope
			float NewRTPCValue = FMath::Clamp((Prop->GetVelocity().Size() - MinMagnetizedSpeed) / (MaxMagnetizedSpeed - MinMagnetizedSpeed), 0.f, 1.f);
			float NewSlope = NewRTPCValue - PreviousRTPCValue;

			// Check if we have a change of slope and need to call the event
			if (NewRTPCValue > 0.0f && NewSlope < 0.0f && PreviousSlope > 0.0f)
			{
				GameInstance->AudioManager()->MagnetizedRTPCStartsDecreasing(Prop);
			}
			PreviousSlope = NewSlope;
			PreviousRTPCValue = NewRTPCValue;

			// Change the RTPC value
			GameInstance->AudioManager()->SetRTPCMagnetizedAmbiance(Prop, NewRTPCValue);
		}
	}
}

/** Update the summon targetting, and returns whether or not the summon can take place in the area */
bool UMagnetPower::UpdateSummonTargetting()
{
	// Do an initial line trace to find the nearest ground surface
	UWorld* const World = GetWorld();
	FHitResult Hit(1.f);
	// Define the start point as the target location of the handles
	FVector Start;
	FRotator Temp;
	Character->GetPhysicHandlesLocationRotation(Start, Temp);
	// Define the end 60m below
	FVector End = Start - FVector(0.0f, 0.0f, 100000.0f);
	// Test the Environment
	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_GameTraceChannel12); // Environment
	World->LineTraceSingleByObjectType(Hit, Start, End, Params, SweepParams);
	DrawDebugLine(World, Start, End, FColor::Orange);

	// If we hit something, do an upward check with the summon check box, with the correct rotation
	if (Hit.IsValidBlockingHit())
	{
		TArray<FHitResult> SummonHits;
		// Add AI and Big props to the sweep
		Params.AddObjectTypesToQuery(ECC_GameTraceChannel1); // AI
		Params.AddObjectTypesToQuery(ECC_GameTraceChannel11); // Big props
		FVector StartSummonSweep = Hit.Location + FVector(0.0f, 0.0f, SummonCheckboxExtent.Z);
		FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartSummonSweep, Character->GetActorLocation());
		LookAtRotator.Pitch = 0.f; // Remove any pitch
		FVector SummonLocation;

		//DrawDebugBoxTraceMulti(World, StartSummonSweep, StartSummonSweep + FVector::UpVector, SummonCheckboxExtent / 2.0f, LookAtRotator, EDrawDebugTrace::ForOneFrame, true, SummonHits, FLinearColor::Blue, FLinearColor::Red, 0.0f);
		//if (World->SweepMultiByObjectType(SummonHits, StartSummonSweep, StartSummonSweep + FVector::UpVector * 0.1f, LookAtRotator.Quaternion(), Params, SummonCheckbox, SweepParams ))
		if (World->SweepMultiByObjectType(SummonHits, StartSummonSweep, StartSummonSweep + FVector::UpVector, LookAtRotator.Quaternion(), Params, SummonCheckbox, SweepParams))
		{
			UE_LOG(LogTemp, Error, TEXT("HIT NUMBER: %i"), SummonHits.Num());
			SummonLocation = SummonHits[0].Location;
		}
		else
		{
			SummonLocation = StartSummonSweep;
		}
		
		DrawDebugBox(World, SummonLocation, SummonCheckboxExtent, LookAtRotator.Quaternion(), FColor::Orange);
		//DrawDebugCapsule(World, SummonLocation, 50.0f, 100.0f, LookAtRotator.Quaternion(), FColor::Orange);
	}

	//// If hit, then check that there is no environment between the player and the ball
	//FVector FinalLocation;
	//if (Hit.IsValidBlockingHit())
	//{
	//	FVector FinalLocation = Hit.Location;
	//	DrawDebugSphere(World, FinalLocation, TelekinesisRadius, 32, FColor::White);

	//	// Raycast to the environment to check that there is nothing blocking
	//	Hit.Reset(1.f, false);
	//	World->LineTraceSingleByChannel(Hit, Start, FinalLocation, ECollisionChannel::ECC_GameTraceChannel2, SweepParams);
	//	FVector BlockingLocation = Hit.IsValidBlockingHit() ? Hit.Location : Hit.TraceEnd;

	//	if (FVector::DistSquared(Character->GetActorLocation(), FinalLocation) <= FVector::DistSquared(Character->GetActorLocation(), BlockingLocation))
	//	{
	//		// TODO: Change HUD + Ball Highlight?
	//		return true;
	//	}
	//}

	// TODO: Change VFX area to red
	return false;
}

