// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncingPower.h"
#include "WQCharacter.h"
#include "BouncingBall.h"

// Sets default values for this component's properties
UBouncingPower::UBouncingPower()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default values
	Identifier = -1;
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
			BouncingBall = World->SpawnActor<ABouncingBall>(BouncingBallBP, Character->GetActorLocation(), Character->GetActorRotation()); // The bouncing ball starts disabled
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BouncingPower: BouncingBallBP not set!"));
	}
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

	if (BounceState == EBounceEnum::BE_BallCharging)
	{
		UpdateBallCharge();
	}
}

// Behaviour when the power is pressed
void UBouncingPower::PowerPressed()
{
	if (BounceState == EBounceEnum::BE_NoBall)
	{
		BounceState = EBounceEnum::BE_BallCharging;
	}
}

// Behaviour when the power is released
void UBouncingPower::PowerReleased()
{
	if (BounceState == EBounceEnum::BE_BallReady)
	{

	}
}

// Update the bouncing
void UBouncingPower::UpdateBallCharge()
{
	
}

