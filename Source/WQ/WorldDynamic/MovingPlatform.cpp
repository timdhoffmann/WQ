// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
	DisableComponentsSimulatePhysics();
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = GetTransform().GetLocation();
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Runs only on the server.
	if (HasAuthority())
	{
		SetActorLocation(GetActorLocation() + FVector::ForwardVector * MoveSpeed /* * FMath::Sin(FVector::Distance(GetTransform().GetLocation(), StartPosition))*/);
	}
}