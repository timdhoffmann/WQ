// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Powers/Power.h"
#include "Managers/EventManager.h"
#include "BouncingPower.generated.h"

/** Enum for the states of the bouncing */
UENUM(BlueprintType)
enum class EBounceEnum : uint8
{
	BE_BallReady 	     UMETA(DisplayName = "BallReady"),
	BE_BallThrown 	     UMETA(DisplayName = "BallThrown"),
	BE_BallCharging	     UMETA(DisplayName = "BallCharging"),
	BE_BallUncharging	 UMETA(DisplayName = "BallUncharging"),
	BE_BallComingBack    UMETA(DisplayName = "BallComingBack"),
};

/**
 * Bouncing power implementation
 */
UCLASS(ClassGroup = (Powers), meta = (BlueprintSpawnableComponent))
class WQ_API UBouncingPower : public UPower
{
	GENERATED_BODY()

public:
	/** Sets default values for this component's properties */
	UBouncingPower();

	/** Called every frame */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Behaviour when the power is activated */
	virtual void SetPowerActive(bool bState) override;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Spawn a Bouncing ball */
	void SpawnBall();

	/** Behaviour when the power is activated */
	virtual void PowerPressed() override;

	/** Behaviour when the power is deactivated */
	virtual void PowerReleased() override;

	/** Update the ball targetting when the ball is thrown, and returns whether or not the ball is targettable */
	bool UpdateBallTargetting();

	/** Propulse the ball after the game feel effects are done */
	UFUNCTION()
	void PropulseBallAfterEffects();

    void UpdateAuraLogic();

	/** Function called on telekinesis finished */
	UFUNCTION()
	void OnTelekinesisFinished();

protected:
	/** State of the bouncing power */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bouncing)
	EBounceEnum BounceState;

	/** Blueprint class of the Bouncing Ball */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bouncing)
	TSubclassOf<class ABouncingBall> BouncingBallBP;

	/** Reference to the actual Bouncing Ball that we will spawn */
	UPROPERTY()
	ABouncingBall* BouncingBall;

	/** Bouncing ball projection force */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing)
	float ProjectionForce;

	/** Telekinesis radius for getting the ball back */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing)
	float TelekinesisRadius;

	/** Telekinesis range for getting the ball back */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing)
	float TelekinesisRange;

	/** Telekinesis force for getting the ball back */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing)
	float TelekinesisForce;

	/** Time limit for when the ball is thrown before it is destroyed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing)
	float ProjectionTimeLimit;

	/** Damage value of the ball when it hits enemies (in Health points) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing)
	int BallDamage;

	/** Duration in seconds of the slow motion just before propulsing the ball */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameFeel)
	float ProjectionSlowDuration;

	/** Time dilation value (> 0.0f (full stop) and < 1.0f ( normal dilation)) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameFeel)
	float ProjectionSlowAmount;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Slowmo )
    bool SlowmoEnabled;

    /** Time duration during which the ball is bouncing and the player is stun (in secs) */
    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Slowmo)
    float SlowmoDelay;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Slowmo)
    float SlowmoDuration;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Slowmo)
    float SlowmoLeverage;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Aura )
    bool AuraEnabled;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Aura )
    float AuraRadius;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Aura )
    float AuraLevitationForce;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Aura)
    float AuraLevitationTime;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Aura)
    float AuraLevitationMaxHeight;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Aura)
    float AuraLevitationMinHeight;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Aura)
    float AuraLevitationAmplitude;

	/** Propulsion Direction */
	FVector PropulsionDirection;

	/** Status of the time limit */
	float CurrentProjectionTime;

	/** Sweep parameters  */
	FCollisionShape Sphere;
	FCollisionQueryParams SweepParams;
	FCollisionQueryParams TelekinesisSweepParams;

    FCollisionShape AuraSphere;
    FCollisionQueryParams AuraSweepParams;
};
