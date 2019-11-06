// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Power.h"
#include "MagnetPower.generated.h"

/**
 * Magnet power implementation
 */
UCLASS( ClassGroup=(Powers), meta=(BlueprintSpawnableComponent) )
class WQ_API UMagnetPower : public UPower
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMagnetPower();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	// Behaviour when the power is activated
	virtual void PowerPressed() override;

	// Behaviour when the power is deactivated
	virtual void PowerReleased() override;

	// Update the magnet (target, objects in it...)
	void UpdateMagnet();

protected:
	// Range of the power
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MagnetRange;

	// Radius of the sphere
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float SphereRadius;

	// Radius of the power
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MagnetRadius;

	// Force of the magnetization
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MagnetForce;

	// Radius coefficient at which the magnetized props will be pulled (0.0 = Center of object, 1.0 = position at which it was pulled)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MagnetizationRadiusCoeff;

	// Propulsion force
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float PropulsionForce;

	// Sweep parameters
	FCollisionShape Sphere;
	FCollisionShape BiggerSphere;
	FCollisionQueryParams SweepParams;

	// Is the magnet targetting activated
	bool bIsTargettingActivated;

	/** Props list */
	UPROPERTY()
	TArray<class AProps*> MagnetizedProps;
};
