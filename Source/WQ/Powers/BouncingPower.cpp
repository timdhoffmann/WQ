// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncingPower.h"
#include "WQCharacter.h"
#include "BouncingBall.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBouncingPower::UBouncingPower()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default values
	Identifier = -1;
	bIsThrownBallReachable = false;
	BallCreationTime = 2.0f;
	BallUnchargingTime = 0.2f;
	FinalScale = FVector(0.3f, 0.3f, 0.3f);
	ProjectionForce = 800000.0f;
}

// Called when the game starts
void UBouncingPower::BeginPlay()
{
	Super::BeginPlay();

	if (BouncingBallBP)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			BouncingBall = World->SpawnActor<ABouncingBall>(BouncingBallBP, Character->GetFireSceneComponent()->GetComponentLocation(), Character->GetActorRotation()); // The bouncing ball starts disabled
			BouncingBall->AttachToComponent(Character->GetFireSceneComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BouncingPower: BouncingBallBP not set!"));
	}

	// Initialize the state
	BounceState = EBounceEnum::BE_BallUncharging;

	// Define sweep params
	SweepParams = FCollisionQueryParams();
	SweepParams.AddIgnoredActor(Character); // Ignore the character in the sweep
	if (BouncingBall)
		SweepParams.AddIgnoredActor(BouncingBall); // Ignore the ball
}

// Behaviour when the power is activated
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

// Called every frame
void UBouncingPower::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if (BounceState == EBounceEnum::BE_BallCharging)
	//{
	//	UpdateBallCharge();
	//}
	//else if (BounceState == EBounceEnum::BE_BallThrown)
	//{

	//}
}

// Behaviour when the power is pressed
void UBouncingPower::PowerPressed()
{
	if (BounceState == EBounceEnum::BE_BallUncharging)
	{
		BounceState = EBounceEnum::BE_BallCharging;
		if (BouncingBall)
			BouncingBall->ChangeScale(FVector::ZeroVector, FinalScale, BallCreationTime, FSimpleCallback::CreateLambda([&] { BounceState = EBounceEnum::BE_BallReady; }));
	}
	else if (BounceState == EBounceEnum::BE_BallThrown)
	{
		if (bIsThrownBallReachable)
		{
			GetBallBack();
		}
	}
}

// Behaviour when the power is released
void UBouncingPower::PowerReleased()
{
	if (BounceState == EBounceEnum::BE_BallCharging)
	{
		BounceState = EBounceEnum::BE_BallUncharging;
		if (BouncingBall)
			BouncingBall->ChangeScale(FinalScale, FVector::ZeroVector, BallUnchargingTime, FSimpleCallback::CreateLambda([] { }));
	}
	else if (BounceState == EBounceEnum::BE_BallReady)
	{
		if (BouncingBall)
		{
			// Trace to see what we should hit
			FHitResult Hit(1.f);

			UWorld* const World = GetWorld();
			FVector Start = UGameplayStatics::GetPlayerCameraManager(World, 0)->GetCameraLocation() + 10.0f * UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector();
			FVector End = Start + 10000.0f * UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector();
			World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_GameTraceChannel10, SweepParams);
			FVector Target = Hit.IsValidBlockingHit() ? Hit.ImpactPoint : Hit.TraceEnd;
			FVector Direction = Target - BouncingBall->GetRootComponent()->GetComponentLocation();
			BouncingBall->Propulse(Direction, ProjectionForce);
		}
	}
}

// Update the bouncing
void UBouncingPower::UpdateBallCharge()
{
}

/** Get the ball back once it's thrown */
void UBouncingPower::GetBallBack()
{

}