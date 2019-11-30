// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
	DisableComponentsSimulatePhysics();
}

void AMovingPlatform::AddActiveTrigger()
{
	/*
	 * Server-only code
	 */
	if (!HasAuthority()) return;

	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	/*
	 * Server-only code
	 */
	if (!HasAuthority()) return;

	// Prevents going below 0 active triggers.
	if (ActiveTriggers <= 0) return;
	ActiveTriggers--;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	// Gets the target's world location since the target location is local to the actor's transform.
	TargetLocation = GetTransform().TransformPosition(LocalTargetLocation);

	/*
	 * Server-only code
	 */
	//if (!HasAuthority()) return;

	SetReplicates(true);
	SetReplicateMovement(true);
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*
	 * Server-only code
	 */
	//if (!HasAuthority()) return;

	// Only moves the platform if enough triggers are active.
	if (ActiveTriggers <= 0) return;

	MovePlatform(DeltaSeconds);
}

void AMovingPlatform::MovePlatform(float DeltaSeconds)
{
	const FVector Location = GetActorLocation();
	const float DistanceTraveled = (Location - StartLocation).Size();
	const float MaxDistance = (TargetLocation - StartLocation).Size();
	if (DistanceTraveled >= MaxDistance)
	{
		const FVector Swap = StartLocation;
		StartLocation = TargetLocation;
		TargetLocation = Swap;
	}

	const FVector Direction = (TargetLocation - StartLocation).GetSafeNormal();
	SetActorLocation(Location + Direction * MoveSpeed * DeltaSeconds);
}