// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Powers/Power.h"
#include "BouncingPower.generated.h"

/** Enum for the states of the bouncing */
UENUM(BlueprintType)
enum class EBounceEnum : uint8
{
	BE_NoBall 	     UMETA(DisplayName = "NoBall"),
	BE_BallReady 	 UMETA(DisplayName = "BallReady"),
	BE_BallThrown 	 UMETA(DisplayName = "BallThrown"),
	BE_BallCharging	 UMETA(DisplayName = "BallCharging")
};

/**
 * Boucing power implementation
 */
UCLASS(ClassGroup = (Powers), meta = (BlueprintSpawnableComponent))
class WQ_API UBouncingPower : public UPower
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBouncingPower();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Behaviour when the power is activated
	virtual void SetPowerActive(bool bState) override;

protected:
	virtual void BeginPlay() override;

	// Behaviour when the power is activated
	virtual void PowerPressed() override;

	// Behaviour when the power is deactivated
	virtual void PowerReleased() override;

	// Update the bouncing
	void UpdateBallCharge();

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
};
