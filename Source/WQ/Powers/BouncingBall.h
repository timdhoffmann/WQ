// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class USceneComponent;
class UPrimitiveComponent;
class UStaticMeshComponent;
class USphereComponent;
class UParticleSystemComponent;
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Managers/EventManager.h"
#include "BouncingBall.generated.h"

/** Enum for the states of the bouncing */
UENUM(BlueprintType)
enum class EBoucingBallEnum : uint8
{
	BBE_General 		UMETA(DisplayName = "General"),
	BBE_Charging	    UMETA(DisplayName = "Charging"),
	BBE_Telekinesis 	UMETA(DisplayName = "TelekinesisdBack"),
};

UCLASS()
class WQ_API ABouncingBall : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties */
	ABouncingBall();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Launches the charge of the ball */
	void Charge(FSimpleCallback Callback);

	/** Stops the charge */
	void StopCharge();

	/** Reset the ball */
	void ResetBall();

	/** Activate/deactivate the ball */
	void SetBallActive(bool bState);

	/** Propulse the ball forward */
	void Propulse(FVector Direction, float Strength);

	/** Get the ball back with telekinesis */
	void GetBallBack(USceneComponent* TargetComponent, float Strength, FSimpleCallback Callback);

	/** Setter for the damage value */
	inline void SetDamage(const float Value) { Damage = Value; }
    
    inline void SetSlowmoState( const bool isEnabled ) { SlowmoEnabled = isEnabled; }
    inline void SetSlowmoDelay( const float delayInSecs ) { SlowmoDelay = delayInSecs; }
    inline void SetSlowmoDuration( const float durationInSecs ) { SlowmoDuration = durationInSecs; }
    inline void SetSlowmoLeverage( const float reductionFactor ) { SlowmoLeverage = reductionFactor; }

protected:

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Changes the simulation physics status */
	void SetPhysicSimulation(bool bState);

	/** Changes the gravity physics status */
	void SetGravitySimulation(bool bState);

	/** Changes the collision profile */
	void SetCollisionProfile(FName CollisionProfileName);

	/** Allows us to call the callback when the Niagara animation is finished playing */
	UFUNCTION()
	void OnChargeComplete(UParticleSystemComponent* ParticleSystem);

	/** Allows us to damage enemies when hit while the ball is thrown */
	UFUNCTION()
	void OnBallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UFUNCTION()
	void TriggerSlowdown(AWQAIEnemy* touchedActor);

protected:
	/** Collider used for the ball */
	UPROPERTY()
	USphereComponent* BallCollider;

	/** Charging particle system used for the ball, assigned in the blueprint */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UParticleSystemComponent* ChargeParticleSystem;

	/** Charging particle system used for the ball, assigned in the blueprint */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* FinishedBallMesh;

	/** State of the ball */
	EBoucingBallEnum State;

	/** Initial scale */
	FVector InitialScale;

	/** Target scale */
	FVector TargetScale;

	/** Current callback for when the scaling/telekinesis is finished */
	FSimpleCallback CurrentCallback;

	/** Reference to the scene component to be telekinesis'd back to */
	USceneComponent* TelekinesisTarget;

	/** Force to be used for the telekinesis */
	float TelekinesisStrength;

	/** Damage value of the ball when it hits enemies */
	int Damage;

    bool SlowmoEnabled;

    bool IsInSlowDown;
    bool isCacac;
    /** Slowdown duration (in seconds) */
    float SlowmoDuration;

    /** Stun time duration (in seconds) */
    float SlowmoDelay;

    float SlowmoLeverage;

    FTimerHandle SlowDownTriggerTimerHandle;

    FVector velocityBackup;
};
