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

	/** Behaviour when the power is activated */
	virtual void PowerPressed() override;

	/** Behaviour when the power is deactivated */
	virtual void PowerReleased() override;

	/** Update the ball targetting when the ball is thrown, and returns whether or not the ball is targettable */
	bool UpdateBallTargetting();

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

	/** Bouncing ball creation time */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing)
	float BallCreationTime;

	/** Bouncing ball reduction time when the power is released while charging */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing)
	float BallUnchargingTime;

	/** Bouncing ball final scale */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing)
	FVector FinalScale;

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

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    bool SlowmoEnabled;

    /** Time duration during which the ball is bouncing and the player is stun (in secs) */
    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    float SlowmoDelay;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    float SlowmoDuration;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    float SlowmoLeverage;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    bool AuraEnabled;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    float AuraRadius;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    float AuraLevitationForce;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    float AuraLevitationTime;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    float AuraLevitationMaxHeight;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    float AuraLevitationMinHeight;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing )
    float AuraLevitationAmplitude;

	/** Status of the time limit */
	float CurrentProjectionTime;

	/** Sweep parameters  */
	FCollisionShape Sphere;
	FCollisionQueryParams SweepParams;
	FCollisionQueryParams TelekinesisSweepParams;

    FCollisionShape AuraSphere;
    FCollisionQueryParams AuraSweepParams;
};
