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

public:
	// Constructor.
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	FVector StartPosition = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MoveSpeed = 10.f;
};
