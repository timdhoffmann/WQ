// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 *
 */
UCLASS()
class WQ_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

#pragma region Variables
private:

	FVector StartLocation = FVector::ZeroVector;
	FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Setup", Meta = (MakeEditWidget = true))
		FVector LocalTargetLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MoveSpeed = 10.f;

	/* The number of currently registered active triggers. */
	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 0;

#pragma endregion

#pragma region Functions
public:

	// Constructor.
	AMovingPlatform();

	/* Registers an active trigger. */
	void AddActiveTrigger();
	/* De-registers an active trigger. */
	void RemoveActiveTrigger();

protected:

	virtual void BeginPlay() override;
	void MovePlatform(float DeltaSeconds);
	virtual void Tick(float DeltaSeconds) override;

#pragma endregion
};
