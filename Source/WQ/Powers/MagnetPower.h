// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Power.h"
#include "MagnetPower.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	// Radius of the power
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MagnetRadius;

	// Sweep parameters
	FCollisionShape Sphere;
	FCollisionQueryParams SweepParams;

	// Is the magnet targetting activated
	bool bIsTargettingActivated;
};
