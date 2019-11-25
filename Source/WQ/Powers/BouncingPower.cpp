// Fill out your copyright notice in the Description page of Project Settings.

#include "BouncingPower.h"
#include "WQCharacter.h"
#include "BouncingBall.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ConstructorHelpers.h"

/** Sets default values for this component's properties */
UBouncingPower::UBouncingPower()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default values
	Identifier = -1;
	ProjectionForce = 800000.0f;
	TelekinesisRadius = 100.0f;
	TelekinesisRange = 10000.0f;
	TelekinesisForce = 50.0f;
	ProjectionTimeLimit = 3.0f;
	BallDamage = 1;
    SlowmoEnabled = true;
    SlowmoDelay = 0.3f;
    SlowmoDuration = 1.0f;
    SlowmoLeverage = 0.1f;

    AuraEnabled = true;
    AuraRadius = 100.0f;
    AuraLevitationForce = 10.0f;
    AuraLevitationTime = 3.0f;
    AuraLevitationMaxHeight = 10.0f;
    AuraLevitationMinHeight = 5.0f;
    AuraLevitationAmplitude = 2.0f;

	// Grabs the references of the BP, here so that we counter the infamous UE4 bug where the references are lost upon reopening
	static ConstructorHelpers::FObjectFinder<UClass> BouncingBallClassFinder(TEXT("Class'/Game/Blueprints/Powers/BP_BouncingBall.BP_BouncingBall_C'"));
	if (BouncingBallClassFinder.Object)
	{
		BouncingBallBP = BouncingBallClassFinder.Object;
	}
}

/** Called when the game starts */
void UBouncingPower::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the ball
	if (BouncingBallBP)
	{
		SpawnBall();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BouncingPower: BouncingBallBP not set!"));
	}

	// Initialize the state
	BounceState = EBounceEnum::BE_BallUncharging;

	// Define sweep params
	Sphere = FCollisionShape::MakeSphere(TelekinesisRadius);
	SweepParams = FCollisionQueryParams();
	TelekinesisSweepParams = FCollisionQueryParams();
	SweepParams.AddIgnoredActor(Character); // Ignore the character in the sweep
	TelekinesisSweepParams.AddIgnoredActor(Character); // Ignore the character in the sweep
	if (BouncingBall)
		SweepParams.AddIgnoredActor(BouncingBall); // Ignore the ball only for the sphere

    AuraSphere = FCollisionShape::MakeSphere( AuraRadius );
    AuraSweepParams = FCollisionQueryParams();
    AuraSweepParams.AddIgnoredActor( Character );

	// Initialize the CurrentProjectionTime
	CurrentProjectionTime = 0.0f;
}

/** Spawn the ball */
void UBouncingPower::SpawnBall()
{
	UWorld* const World = GetWorld();
	if (World)
	{
		BouncingBall = World->SpawnActor<ABouncingBall>(BouncingBallBP, Character->GetFireSceneComponent()->GetComponentLocation(), Character->GetActorRotation()); // The bouncing ball starts disabled
		BouncingBall->AttachToComponent(Character->GetFireSceneComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		BouncingBall->SetDamage(BallDamage);
		BouncingBall->SetSlowmoState(SlowmoEnabled);
		BouncingBall->SetSlowmoDelay(SlowmoDelay);
		BouncingBall->SetSlowmoDuration(SlowmoDuration);
		BouncingBall->SetSlowmoLeverage(SlowmoLeverage);
	}
}

/** Behaviour when the power is activated */
void UBouncingPower::SetPowerActive(bool bState)
{
	if (bState)
	{
		// Subscribe to the correct events
		Character->OnFirePressed().AddUFunction(this, TEXT("PowerPressed"));
		Character->OnFireReleased().AddUFunction(this, TEXT("PowerReleased"));
	}
	else
	{
		// Unsubscribe
		Character->OnFirePressed().RemoveAll(this);
		Character->OnFireReleased().RemoveAll(this);
	}
}

/** Called every frame */
void UBouncingPower::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (BounceState == EBounceEnum::BE_BallThrown)
	{
		// Time limit logic
		CurrentProjectionTime += DeltaTime;
		if (CurrentProjectionTime >= ProjectionTimeLimit)
		{
			BounceState = EBounceEnum::BE_BallUncharging;

			// Reset the ball
			BouncingBall->ResetBall();
			BouncingBall->AttachToComponent(Character->GetFireSceneComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			return;
		}

		// Logic for getting the ball back
		UpdateBallTargetting();
	}
    else if ( BounceState == EBounceEnum::BE_BallReady )
    {
        UpdateAuraLogic();
    }
}

/** Behaviour when the power is pressed */
void UBouncingPower::PowerPressed()
{
	// Charge the ball if it's uncharging
	if (BounceState == EBounceEnum::BE_BallUncharging)
	{
		BounceState = EBounceEnum::BE_BallCharging;
		// Spawn a ball if the previous one has disappeared
		if (!IsValid(BouncingBall))
		{
			SpawnBall();
		}
		BouncingBall->Charge(FSimpleCallback::CreateLambda([&] { BounceState = EBounceEnum::BE_BallReady; }));
	}
	// Else try to get the ball back if it's thrown
	else if (BounceState == EBounceEnum::BE_BallThrown)
	{
		if (UpdateBallTargetting())
		{
			BouncingBall->GetBallBack(Character->GetFireSceneComponent(), TelekinesisForce, FSimpleCallback::CreateUFunction(this, TEXT("OnTelekinesisFinished")));
			BounceState = EBounceEnum::BE_BallComingBack;
		}
	}
}

/** Behaviour when the power is released */
void UBouncingPower::PowerReleased()
{
	// If the ball is still charging, uncharge it
	if (BounceState == EBounceEnum::BE_BallCharging)
	{
		BounceState = EBounceEnum::BE_BallUncharging;
		if (IsValid(BouncingBall))
		{
			BouncingBall->StopCharge();
		}
	}
	// Else if the ball is ready, throw it
	else if (BounceState == EBounceEnum::BE_BallReady)
	{
		if (IsValid(BouncingBall))
		{
			// Trace to see what we should hit
			FHitResult Hit(1.f);
			UWorld* const World = GetWorld();
			FVector Start = UGameplayStatics::GetPlayerCameraManager(World, 0)->GetCameraLocation() + 10.0f * UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector();
			FVector End = Start + 10000.0f * UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector();
			World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, SweepParams);

			// Propulse the ball
			FVector Target = Hit.IsValidBlockingHit() ? Hit.ImpactPoint : Hit.TraceEnd;
			FVector Direction = Target - BouncingBall->GetRootComponent()->GetComponentLocation();
			BouncingBall->Propulse(Direction, ProjectionForce);

			// Change the state parameters
			BounceState = EBounceEnum::BE_BallThrown;
			CurrentProjectionTime = 0.0f;
		}
	}
}

/** Update the ball targetting when the ball is thrown */
bool UBouncingPower::UpdateBallTargetting()
{
	// Do an initial sphere sweep with only the ball trace channel
	UWorld* const World = GetWorld();
	FHitResult Hit(1.f);
	FVector Start = UGameplayStatics::GetPlayerCameraManager(World, 0)->GetCameraLocation() + 10.0f * UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector();
	FVector End = Start + TelekinesisRange * UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector();
	World->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECC_GameTraceChannel10, Sphere, TelekinesisSweepParams);
	
	// If hit, then check that there is no environment between the player and the ball
	FVector FinalLocation;
	if (Hit.IsValidBlockingHit())
	{
		FVector FinalLocation = Hit.Location;
		DrawDebugSphere(World, FinalLocation, TelekinesisRadius, 32, FColor::White);

		// Raycast to the environment to check that there is nothing blocking
		Hit.Reset(1.f, false);
		World->LineTraceSingleByChannel(Hit, Start, FinalLocation, ECollisionChannel::ECC_GameTraceChannel2, SweepParams);
		FVector BlockingLocation = Hit.IsValidBlockingHit() ? Hit.Location : Hit.TraceEnd;

		if (FVector::DistSquared(Character->GetActorLocation(), FinalLocation) <= FVector::DistSquared(Character->GetActorLocation(), BlockingLocation))
		{
			// TODO: Change HUD + Ball Highlight?
			return true;
		}
	}

	// TODO: Reset HUD
	return false;
}

void UBouncingPower::UpdateAuraLogic()
{
    //// Do an initial sphere sweep with only the ball trace channel
    //UWorld* const World = GetWorld();
    //FHitResult Hit( 1.f );
    //FVector Start = UGameplayStatics::GetPlayerCameraManager( World, 0 )->GetCameraLocation() + 10.0f * UGameplayStatics::GetPlayerCameraManager( World, 0 )->GetActorForwardVector();
    //FVector End = Start + AuraRadius * UGameplayStatics::GetPlayerCameraManager( World, 0 )->GetActorForwardVector();
    //World->SweepSingleByChannel( Hit, Start, End, FQuat::Identity,ECC_GameTraceChannel10, Sphere, TelekinesisSweepParams );

    //// If hit, then check that there is no environment between the player and the ball
    //FVector FinalLocation;
    //if ( Hit.IsValidBlockingHit() ) {
    //    FVector FinalLocation = Hit.Location;
    //    DrawDebugSphere( World, FinalLocation, AuraRadius, 32, FColor::White );

    //    // Raycast to the environment to check that there is nothing blocking
    //    Hit.Reset( 1.f, false );
    //    World->LineTraceSingleByChannel( Hit, Start, FinalLocation, ECollisionChannel::ECC_GameTraceChannel2, SweepParams );
    //    FVector BlockingLocation = Hit.IsValidBlockingHit() ? Hit.Location : Hit.TraceEnd;

    //    if ( FVector::DistSquared( Character->GetActorLocation(), FinalLocation ) <= FVector::DistSquared( Character->GetActorLocation(), BlockingLocation ) ) {
    //        Hit.Actor->SetActorHiddenInGame( true );
    //    }
    //}
}

/** Function called on telekinesis finished */
void UBouncingPower::OnTelekinesisFinished()
{
	BounceState = EBounceEnum::BE_BallReady;
	BouncingBall->AttachToComponent(Character->GetFireSceneComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}