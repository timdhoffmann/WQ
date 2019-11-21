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
	/** Sets default values for this component's properties */
	UMagnetPower();

	/** Called every frame */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Behaviour when the power is activated */
	virtual void PowerPressed() override;

	/** Behaviour when the power is deactivated */
	virtual void PowerReleased() override;

	/** Update the magnet (target, objects in it...) */
	void UpdateMagnet();

	/** Update the audio RTPC of the magnetized props */
	void UpdateMagnetRTPC();

protected:
	/** Range of the power */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MagnetRange;

	/** Radius of the center sphere colliding with the environment */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float SphereRadius;

	/** Actual radius of the power, radius at which the objects are attracted */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MagnetRadius;

	/** Force of the magnetization */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MagnetForce;

	/** Radius coefficient at which the magnetized props will be pulled (0.0 = Center of object, 1.0 = position at which it was pulled) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MagnetizationRadiusCoeff;

	/** Propulsion force at which the objects are projected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float PropulsionForce;

	/** Blueprint class of the indicator */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	TSubclassOf<class AMagnetIndicator> MagnetIndicatorBP;

	/** Min speed for the RTPC ambiance values (speed value at which the RTPC is set to 0) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MinMagnetizedSpeed;

	/** Max speed for the RTPC ambiance values (speed value at which the RTPC is set to 1) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MaxMagnetizedSpeed;

	/** Used to track the change of RTPC acceleration (if it increases or decreases) */
	float PreviousRTPCValue;
	float PreviousSlope;

	/** Reference to the indicator that will be spawned */
	UPROPERTY()
	AMagnetIndicator* MagnetIndicator;

	/** Sweep parameters */
	FCollisionShape Sphere;
	FCollisionShape BiggerSphere;
	FCollisionQueryParams SweepParams;

	/** Is the magnet targetting activated */
	bool bIsTargettingActivated;

	/** Props list */
	UPROPERTY()
	TArray<class AProps*> MagnetizedProps;

	/** Temporary materials for video */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UMaterial* Mat1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterial* Mat2;
};
