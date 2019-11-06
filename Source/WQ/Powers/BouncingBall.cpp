// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncingBall.h"
#include "Math/UnrealMathUtility.h"
#include "StaticUtils.h"

// Sets default values
ABouncingBall::ABouncingBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	bIsBallResizing = false;
	TargetScale = FVector::OneVector;
	CurrentScalingStatus = 0.0f;
	CurrentScalingSpeed = 0.0f;
}

// Called when the game starts or when spawned
void ABouncingBall::BeginPlay()
{
	Super::BeginPlay();
	
	// Activate all elements with zero scale, and disable physics
	SetBallActive(true);
	GetRootComponent()->SetWorldScale3D(FVector::ZeroVector);
	SetPhysicSimulation(false);
	SetCollisionProfile(TEXT("BallHeld"));
}

// Called every frame
void ABouncingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsBallResizing)
	{
		CurrentScalingStatus = FMath::Min(1.0f, CurrentScalingStatus + DeltaTime * CurrentScalingSpeed);

		GetRootComponent()->SetWorldScale3D(FMath::Lerp<FVector>(InitialScale, TargetScale, CurrentScalingStatus));

		if (CurrentScalingStatus >= 1.0f)
		{
			CurrentCallback.ExecuteIfBound();
			bIsBallResizing = false;
			CurrentCallback.Unbind();
		}
	}
}

void ABouncingBall::ChangeScale(FVector InitialScale, FVector FinalScale, float Duration, FSimpleCallback Callback)
{
	this->InitialScale = InitialScale;
	this->TargetScale = FinalScale;
	bIsBallResizing = true;

	CurrentScalingSpeed = 1 / Duration;

	// Takes the hypothesis that all dimensions will be scaled the same
	FVector CurrentScale = GetRootComponent()->GetComponentScale();
	CurrentScalingStatus = FMath::Abs((CurrentScale.X - InitialScale.X) / (TargetScale.X - InitialScale.X));

	// Update the new resizing callback
	CurrentCallback.Unbind();
	CurrentCallback = Callback;
}

/** Activate/deactivate the ball */
void ABouncingBall::SetBallActive(bool bState)
{
	for (UStaticMeshComponent* Mesh : BallMeshes)
	{
		Mesh->SetActive(bState);
		Mesh->SetHiddenInGame(!bState);
	}
}

/** Changes the simulation physics status */
void ABouncingBall::SetPhysicSimulation(bool bState)
{
	for (UStaticMeshComponent* Mesh : BallMeshes)
	{
		if (Mesh != nullptr)
		{
			Mesh->SetSimulatePhysics(bState);
			if (bState)
			{
				Mesh->WakeAllRigidBodies();
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BouncingBall: MESH NOT DEFINED!"));
		}
	}
}

/** Changes the gravity physics status */
void ABouncingBall::SetGravitySimulation(bool bState)
{
	for (UStaticMeshComponent* Mesh : BallMeshes)
	{
		if (Mesh != nullptr)
		{
			Mesh->SetEnableGravity(bState);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BouncingBall: MESH NOT DEFINED!"));
		}
	}
}

/** Changes the collision profile */
void ABouncingBall::SetCollisionProfile(FName CollisionProfileName)
{
	for (UStaticMeshComponent* Mesh : BallMeshes)
	{
		if (Mesh != nullptr)
		{
			Mesh->SetCollisionProfileName(CollisionProfileName);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BouncingBall: MESH NOT DEFINED!"));
		}
	}
}

/** Propulse the ball forward */
void ABouncingBall::Propulse(FVector Direction, float Strength)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	for (UStaticMeshComponent* Mesh : BallMeshes)
	{
		if (Mesh != nullptr)
		{
			SetCollisionProfile(TEXT("Ball"));
			SetPhysicSimulation(true);
			Mesh->AddForce(UStaticUtils::GetSafeNormal(Direction) * Strength * Mesh->GetMassScale(), NAME_None, true);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BouncingBall: MESH NOT DEFINED!"));
		}
	}
}

