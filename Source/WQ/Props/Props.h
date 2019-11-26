// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UMaterialInstanceDynamic;
class UMeshComponent;
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Props.generated.h"

UCLASS()
class WQ_API AProps : public APawn
{
	GENERATED_BODY()

public:
	/** Sets default values for this pawn's properties */
	AProps();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Changes the simulation physics status */
	void SetPhysicSimulation(bool bState);

	/** Changes the gravity physics status */
	void SetGravitySimulation(bool bState);

	///** Remove gravity and make the fly stop when there is a collision */
	//void PrepareFly();

	/** Remove physical sims, move the prop towards a target */
	void FlyTowards(FVector Target, float Speed);

	/** Stop the flying */
	void FlyStop();

	/** Propulse physically */
	void Propulse(FVector Direction, float Strength);

	/** Set the material glowing, Duration of 0.0f means infinite */
	void SetGlow(float Multiplier, float Duration = 0.0f, FLinearColor Color = FLinearColor::Black, bool bShouldRandPropulse = false);

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

protected:
	/** Root mesh component of the props */
	UPROPERTY()
	UMeshComponent* Mesh;

	/** Movement component of the props */
	UPROPERTY()
	class UPropsMovement* PropsMovementComponent;

	/** Dynamic material instance to modify properties during runtime */
	UPROPERTY()
	UMaterialInstanceDynamic* MatInstanceDynamic;

	/** Tracks the glowing status */
	bool bIsGlowing;
	/** Tracks the glowing elapsed time */
	float GlowElapsed;
	/** Tracks the glowing current duration */
	float GlowSpeed;
	/** Tracks the glowing multiplier */
	float InitialGlowMultiplier;
	/** Tracks the glowing multiplier */
	float TargetGlowMultiplier;
	/** Tracks the initial Emissive Color of the material */
	FLinearColor InitialEmissiveColor;
	/** Tracks the target Emissive Color of the material */
	FLinearColor TargetEmissiveColor;
};
