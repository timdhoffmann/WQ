// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class USceneComponent;
class UPrimitiveComponent;
class UStaticMeshComponent;
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Managers/EventManager.h"
#include "BouncingBall.generated.h"

UCLASS()
class WQ_API ABouncingBall : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties */
	ABouncingBall();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Changes the scale of the ball elements in a given time */
	void ChangeScale(FVector InitialScale, FVector FinalScale, float Duration, FSimpleCallback Callback);

	/** Activate/deactivate the ball */
	void SetBallActive(bool bState);

	/** Propulse the ball forward */
	void Propulse(FVector Direction, float Strength);

	/** Get the ball back with telekinesis */
	void GetBallBack(USceneComponent* TargetComponent, float Strength, FSimpleCallback Callback);

	/** Reset the ball position and scale */
	void ResetBall();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Changes the simulation physics status */
	void SetPhysicSimulation(bool bState);

	/** Changes the gravity physics status */
	void SetGravitySimulation(bool bState);

	/** Changes the collision profile */
	void SetCollisionProfile(FName CollisionProfileName);

	///** Allows us to remove durability when the ball hits the environment */
	//UFUNCTION()
	//void OnBallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bouncing)
	//TArray<UStaticMeshComponent*> BallMeshes;
	// Mesh used for the ball
	UPROPERTY()
	UStaticMeshComponent* BallMesh;

	/** Is the ball resizing? */
	bool bIsBallResizing;

	/** Is current telekinesis'd back ? */
	bool bIsBallTelekinesisd;

	/** Initial scale */
	FVector InitialScale;

	/** Target scale */
	FVector TargetScale;

	/** Current scaling status */
	float CurrentScalingStatus;

	/** Current scaling speed */
	float CurrentScalingSpeed;

	/** Current callback for when the scaling/telekinesis is finished */
	FSimpleCallback CurrentCallback;

	/** Reference to the scene component to be telekinesis'd back to */
	USceneComponent* TelekinesisTarget;

	/** Force to be used for the telekinesis */
	float TelekinesisStrength;
};
