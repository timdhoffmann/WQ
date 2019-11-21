// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WQCharacter.generated.h"
class UInputComponent;
class UWQGameInstance;
class UCameraShake;
class UCurveFloat;

DECLARE_EVENT(AWQCharacter, FPowerPressed)
DECLARE_EVENT(AWQCharacter, FPowerReleased)
DECLARE_EVENT(AWQCharacter, FFirePressed)
DECLARE_EVENT(AWQCharacter, FFireReleased)

UCLASS(config=Game)
class AWQCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWQCharacter();

	///** Returns Mesh1P subobject **/
	//FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/** Returns the Power Location scene component **/
	class USceneComponent* GetFireSceneComponent() const { return FP_FireSceneComponent; }
	
	/** Returns the Physic Handles */
	TArray<class UPhysicsHandleComponent*> GetPhysicHandles() const { return PhysicHandles; }

	/** Get or add a physic handle and returns a ref to it */
	UPhysicsHandleComponent* GetUnusedPhysicHandle();

	/** Clear all physic handle */
	void ClearAllPhysicHandle();

	/** Accessor to the power events */
	FPowerPressed& OnPowerPressed() { return PowerPressedEvent; }
	FPowerReleased& OnPowerReleased() { return PowerReleasedEvent; }

	/** Accessor to the fire events */
	FFirePressed& OnFirePressed() { return FirePressedEvent; }
	FFireReleased& OnFireReleased() { return FireReleasedEvent; }

protected:
	virtual void BeginPlay();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/** Handles player running */
	void Run();

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

	/** Fire binding methods, called by the input */
	UFUNCTION()
	void FirePressed();

	UFUNCTION()
	void FireReleased();

	/** Power switching methods, called by the input */
	UFUNCTION()
	void SwitchPowerUp();
	UFUNCTION()
	void SwitchPowerDown();

	/** Pause behaviour */
    UFUNCTION()
    void PauseTriggered();

	/** Add a physic handle */
	void AddPhysicHandle(int Index, bool bIsRuntime = false);

protected:
	///** Pawn mesh: 1st person view (arms; seen only by self) */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	//class USkeletalMeshComponent* Mesh1P;

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

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** HeadBob shake blueprints */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Headbob)
	TSubclassOf<UCameraShake> WalkingHeadbobShake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Headbob)
	TSubclassOf<UCameraShake> RunningHeadbobShake;

	/** Current headbob shake pointer */
	TSubclassOf<UCameraShake> HeadbobShake;

	/** Normal footsteps interval in distance (cm) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Footsteps)
	float NormalFootstepsInterval;

	/** Running footsteps interval in distance (cm) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Footsteps)
	float RunningFootstepsInterval;

	/** Walking speed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	float WalkingSpeed;

	/** Walking acceleration */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	float WalkingAcceleration;

	/** Running speed when shift is pressed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	float RunningSpeed;

	/** Walking acceleration */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	float RunningAcceleration;

	/** FOV change curve during running */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blink)
	UCurveFloat* FOVMultiplierCurve;

	/** Initial FOV value */
	float InititialFOV;

	/** Used to track the status of the FOV change during running */
	float ElapsedFOV;
	float MinTimeFOV;
	float MaxTimeFOV;

	/** Current status of the footsteps interval */
	float CurrentFootstepsInterval;

	/** Current status of the footsteps distance */
	float FootstepsStatus;

	/** Has the footstep sound when the character is stopping been played ? */
	bool bLastFootstepPlayed;

	/** Location of the character in the last frame */
	FVector LastLocation;

	/** Called when the player presses the power input */
	FPowerPressed PowerPressedEvent;

	/** Called when the player releases the power input */
	FPowerReleased PowerReleasedEvent;

	/** Called when the player presses the fire input */
	FFirePressed FirePressedEvent;

	/** Called when the player releases the fire input */
	FFireReleased FireReleasedEvent;

	/** Location of the effects of the power */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Powers)
	USceneComponent* FP_FireSceneComponent;

	/** Physic handles list */
	UPROPERTY()
	TArray<UPhysicsHandleComponent*> PhysicHandles;

	/** Current number of physic handles used */
	int HandlesUsed;

	/** List of powers */
	UPROPERTY()
	TArray<class UPower*> Powers;

	/** Index of the current power */
	int PowerIndex;

	/** Game instance pointer */
	UWQGameInstance* GameInstance;

	/** Tracks the running status */
	bool bIsRunning;
};

