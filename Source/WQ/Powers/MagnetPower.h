// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AWQAIGolem;
class AMagnetIndicator;
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Power.h"
#include "MagnetPower.generated.h"

/** Enum for the states of the magnet */
UENUM(BlueprintType)
enum class EMagnetEnum : uint8
{
	ME_None 			 UMETA(DisplayName = "MagnetNone"),
	ME_Targetting 	     UMETA(DisplayName = "MagnetTargetting"),
	ME_Summoning	     UMETA(DisplayName = "MagnetSummoning"),
};

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

	/** Behaviour when the power is activated */
	virtual void SetPowerActive(bool bState) override;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Behaviour when the power is activated */
	virtual void PowerPressed() override;
	/** Behaviour when the power is deactivated */
	virtual void PowerReleased() override;

	/** Behaviour when the summon action is pressed */
	UFUNCTION()
	void SummonPressed();
	/** Behaviour when the summon action is released */
	UFUNCTION()
	void SummonReleased();

	/** Update the magnet (target, objects in it...) */
	void UpdateMagnet();

	/** Update the audio RTPC of the magnetized props */
	void UpdateMagnetRTPC();

	/** Update the summon targetting, and returns whether or not the summon can take place in the area */
	bool UpdateSummonTargetting();

	/** Removes all magnetized props */
	void StopMagnet();

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
	TSubclassOf<AMagnetIndicator> MagnetIndicatorBP;

	/** Min speed for the RTPC ambiance values (speed value at which the RTPC is set to 0) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MinMagnetizedSpeed;

	/** Max speed for the RTPC ambiance values (speed value at which the RTPC is set to 1) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float MaxMagnetizedSpeed;

	/** Glow multiplier of the props when held */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magnet")
	float GlowMultiplier;

	/** Minimal amount of props held by the magnet to summon a golem */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Summon")
	int MinPropsAmountToSummon;

	/** Props glowing color to indicate that there is not enough props to summon a golem */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Summon")
	FLinearColor DeniedSummonColor;

	/** Denied summon glow total duration (initial color -> denied color -> initial color) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Summon")
	float DeniedSummonGlowDuration;

	/** Denied summon glow multiplier (initial multiplier -> denied multiplier -> initial multiplier) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Summon")
	float DeniedSummonGlowMultiplier;

	/** Check box extent (size of the cube used to test whether or not a zone can spawn a golem) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Summon")
	FVector SummonCheckboxExtent;

	/** Speed at which the props will assemble together to form the golem */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Summon")
	float SummonAssemblySpeed;

	/** Blueprint class of the golem */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Summon")
	TSubclassOf<AWQAIGolem> GolemBP;

	/** State of the magnet power */
	EMagnetEnum MagnetState;

	/** Used to track the change of RTPC acceleration (if it increases or decreases) */
	float PreviousRTPCValue;
	float PreviousSlope;

	/** Reference to the indicator that will be spawned */
	UPROPERTY()
	AMagnetIndicator* MagnetIndicator;

	/** Sweep parameters */
	FCollisionShape Sphere;
	FCollisionShape BiggerSphere;
	FCollisionShape SummonCheckbox;
	FCollisionQueryParams SweepParams;

	/** Props list */
	UPROPERTY()
	TArray<class AProps*> MagnetizedProps;

	/** Summoning location */
	FVector SummoningLocation;
};
