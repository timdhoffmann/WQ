// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Props.generated.h"

UCLASS()
class WQ_API AProps : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AProps();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Changes the simulation physics status */
	void SetPhysicSimulation(bool bState);

	/** Changes the gravity physics status */
	void SetGravitySimulation(bool bState);

	///** Remove gravity and make the fly stop when there is a collision */
	//void PrepareFly();

	/** Remove physical sims, move the prop towards a target */
	void FlyTowards(class USceneComponent* NewParent, float Speed, float MagnetizationRadius);

	/** Stop the flying */
	void FlyStop();

	/** Propulse physically */
	void Propulse(FVector Direction, float Strength);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	/** Root mesh component of the props */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Props")
	class UMeshComponent* Mesh;

	/** Movement component of the props */
	UPROPERTY()
	class UPropsMovement* PropsMovementComponent;

	/** Is currently flying towards a target ? */
	bool bIsFlying;

	/** Current target */
	FVector FlyingTarget;
};
