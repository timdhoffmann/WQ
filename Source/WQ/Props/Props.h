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

	/** Move the prop towards a target, make it stop when there is a collision */
	void FlyTowards(float ForceAmplitude, FVector Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Make the fly stop when there is a collision */
	UFUNCTION()
	void StopFly(class UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	/** Root mesh component of the props */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Props")
	class UMeshComponent* Mesh;

	/** Movement component of the props */
	UPROPERTY()
	class UPropsMovement* PropsMovementComponent;
};
