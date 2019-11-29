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

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	StartLocation = GetTransform().GetLocation();
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Runs only on the server.
	if (HasAuthority())
	{
		FVector ActorLocation = GetActorLocation();
		const FVector TargetWorldLocation = GetTransform().TransformPosition(TargetLocation);
		const FVector TargetDirectionNormal = (TargetWorldLocation - ActorLocation).GetSafeNormal(0.01f);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), TargetDirectionNormal.IsNormalized() ? TEXT("True") : TEXT("False"));
		ActorLocation += TargetDirectionNormal * MoveSpeed * DeltaSeconds;
		SetActorLocation(ActorLocation /* * FMath::Sin(FVector::Distance(GetTransform().GetLocation(), StartLocation))*/);
	}
}