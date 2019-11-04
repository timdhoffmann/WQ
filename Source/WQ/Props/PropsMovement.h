// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PropsMovement.generated.h"

/**
 * Movement component that provides simple movement for any Pawn class.
 * Integrates functionality from UFloatingPawnMovement and gravity is implemented.
 *
 * Normally the root component of the owning actor is moved, however another component may be selected (see SetUpdatedComponent()).
 * During swept (non-teleporting) movement only collision of UpdatedComponent is considered, attached components will teleport to the end location ignoring collision.
 */
UCLASS(ClassGroup = Movement, meta = (BlueprintSpawnableComponent))
class WQ_API UPropsMovement : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	// Sets default values
	UPropsMovement(const FObjectInitializer& ObjectInitializer);

	/** Enables/Disables the gravity */
	UFUNCTION(BlueprintCallable, Category = "PropsMovement")
	void SetGravity(bool bState);

	virtual float GetMaxSpeed() const override { return MaxSpeed; }

	virtual void MoveAutomaticallyTo(class USceneComponent* Target, float Speed);

	virtual void StopAutomaticMovement();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool ResolvePenetrationImpl(const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotation) override;

	/** Calculates the fall velocity */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector ComputeFallVelocity(const FVector& InitialVelocity, float DeltaTime) const;

	/** Update Velocity based on input. Also applies gravity. */
	virtual void ApplyControlInputToVelocity(float DeltaTime);

	/** Prevent Pawn from leaving the world bounds (if that restriction is enabled in WorldSettings) */
	virtual bool LimitWorldBounds();

protected:
	/** Maximum velocity magnitude allowed for the controlled Pawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PropsMovement")
	float MaxSpeed;

	/** Acceleration applied by input (rate of change of velocity) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PropsMovement")
	float Acceleration;

	/** Deceleration applied when there is no input (rate of change of velocity) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PropsMovement")
	float Deceleration;

	/**
	* Setting affecting extra force applied when changing direction, making turns have less drift and become more responsive.
	* Velocity magnitude is not allowed to increase, that only happens due to normal acceleration. It may decrease with large direction changes.
	* Larger values apply extra force to reach the target direction more quickly, while a zero value disables any extra turn force.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FloatingPawnMovement, meta = (ClampMin = "0", UIMin = "0"))
	float TurningBoost;

	/** Whether or not the gravity is enabled */
	UPROPERTY()
	bool bIsGravityEnabled;

	/** Max falling velocity of the object */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float TerminalVelocity;

	/** Gravity direction of the object */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	FVector Gravity;

	/** Set to true when a position correction is applied. Used to avoid recalculating velocity when this occurs. */
	UPROPERTY(Transient)
	uint32 bPositionCorrected : 1;

	/** Should the prop move automatically towards a target ? */
	bool bShouldMoveAutomatically;

	/** Automatic movement target */
	USceneComponent* MoveTarget;

	/** Automatic movement speed */
	float AutomaticMovementSpeed;

	/** Sweep parameters for the collision check when moving automatically */
	FCollisionQueryParams SweepParams;
};
