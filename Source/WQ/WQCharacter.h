// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WQCharacter.generated.h"

class UInputComponent;

DECLARE_EVENT(AWQCharacter, FPowerPressed)
DECLARE_EVENT(AWQCharacter, FPowerReleased)

UCLASS(config=Game)
class AWQCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWQCharacter();

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/** Returns the Power Location scene component **/
	class USceneComponent* GetPowerLocation() const { return FP_PowerLocation; }
	//class UPhysicsHandleComponent* GetPhysicsPowerLocation() const { return FP_PhysicsPowerLocation; }

	// Accessor to the power events
	FPowerPressed& OnPowerPressed() { return PowerPressedEvent; }
	FPowerReleased& OnPowerReleased() { return PowerReleasedEvent; }

protected:
	virtual void BeginPlay();

	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/** Power binding methods, called by the input */
	UFUNCTION()
	void PowerPressed();
	UFUNCTION()
	void PowerReleased();

protected:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AWQProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** HeadBob shake blueprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Headbob)
	TSubclassOf<class UCameraShake> HeadbobShake;

	// Called when the player presses the power input
	FPowerPressed PowerPressedEvent;

	// Called when the player releases the power input
	FPowerReleased PowerReleasedEvent;

	/** Location of the effects of the power */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Power)
	USceneComponent* FP_PowerLocation;

	///** Location of the effects of the power, for physical simulations */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Power)
	//UPhysicsHandleComponent* FP_PhysicsPowerLocation;
};

