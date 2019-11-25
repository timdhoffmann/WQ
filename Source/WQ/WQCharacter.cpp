// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WQCharacter.h"
#include "WQProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "Managers/WQGameInstance.h"
#include "Managers/AudioManager.h"
#include "Managers/EventManager.h"
#include "Managers/PauseManager.h"
#include "Math/UnrealMathUtility.h"
#include "Powers/Power.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISense_Sight.h"
#include "Runtime/AIModule/Classes/Perception/AISense_Hearing.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AWQCharacter

AWQCharacter::AWQCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Create the needed handles
	for (int i = 0; i < 10; i++)
	{
		AddPhysicHandle(i);
	}
	HandlesUsed = 0;
	NormalFootstepsInterval = 350.0f;
	RunningFootstepsInterval = 350.0f;
	FootstepsStatus = 0.0f;
	bLastFootstepPlayed = true;
	bIsRunning = false;
	WalkingSpeed = 600.0f;
	WalkingAcceleration = 2048.0f;
	RunningSpeed = 1200.0f;
	RunningAcceleration = 5096.0f;
	ElapsedFOV = 0.0f;
	bShouldRunInputBeConsumed = false;
}

void AWQCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

    UAIPerceptionSystem::RegisterPerceptionStimuliSource( this, UAISense_Sight::StaticClass(), this );
    UAIPerceptionSystem::RegisterPerceptionStimuliSource( this, UAISense_Hearing::StaticClass(), this );

	//// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	//Mesh1P->SetHiddenInGame(false, true);

	// Get all the powers attached and sort them by identifier
	GetComponents<UPower>(Powers);
	Powers.Sort([](const UPower& A, const UPower& B) {
		return A.GetIdentifier() < B.GetIdentifier();
		});

	// Activate the fire and the first power
	PowerIndex = 0;
	if (Powers.Num() > 0)
	{
		Powers[PowerIndex]->SetPowerActive(true); // Fire
	}
	if (Powers.Num() > 1)
	{
		PowerIndex++;
		Powers[PowerIndex]->SetPowerActive(true); // First power
	}

	// Initialize the footsteps variables
	LastLocation = GetActorLocation();
	CurrentFootstepsInterval = NormalFootstepsInterval;

	// Initialize the Game Instance
	GameInstance = Cast<UWQGameInstance>(GetGameInstance());
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("WQCharacter: GameInstance not found!"));
	}

	// Initialize the walking speed
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	GetCharacterMovement()->MaxAcceleration = WalkingAcceleration;

	// Intialize the Headbob
	HeadbobShake = WalkingHeadbobShake;

	// Setup the initial FOV needs
	InititialFOV = GetFirstPersonCameraComponent()->FieldOfView;
	if (IsValid(FOVMultiplierCurve))
	{
		FOVMultiplierCurve->GetTimeRange(MinTimeFOV, MaxTimeFOV);
	}
}

void AWQCharacter::Tick(float DeltaTime)
{
	// Consume the run input if needed
	if (bShouldRunInputBeConsumed && !GetCharacterMovement()->IsFalling())
	{
		bIsRunning = true;
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
		GetCharacterMovement()->MaxAcceleration = RunningAcceleration;
		HeadbobShake = RunningHeadbobShake;
	}

	FVector HorizontalVelocity = FVector(GetVelocity().X, GetVelocity().Y, 0.0f);
	if (HorizontalVelocity.SizeSquared() != 0.0f) // If we have horizontal movement
	{
		// Running FOV change logic
		if (bIsRunning)
		{
			ElapsedFOV += DeltaTime;
			ElapsedFOV = FMath::Min(ElapsedFOV, MaxTimeFOV);
		}
		else
		{
			ElapsedFOV -= DeltaTime;
			ElapsedFOV = FMath::Max(ElapsedFOV, MinTimeFOV);
		}

		// Continue the logic for playing footsteps
		if (!bWasJumping)
		{
			bLastFootstepPlayed = false;
			FootstepsStatus += (GetActorLocation() - LastLocation).Size();
			LastLocation = GetActorLocation();
			if (FootstepsStatus >= CurrentFootstepsInterval)
			{
				FootstepsStatus = 0.0f;
				if (IsValid(GameInstance))
				{
					GameInstance->AudioManager()->PlayFootsteps(this);
				}
			}
		}
	}
	else // Else if we are not moving horizontally
	{
		if (!bLastFootstepPlayed)
		{
			bLastFootstepPlayed = true;
			FootstepsStatus = 0.0f;
			if (IsValid(GameInstance))
			{
				GameInstance->AudioManager()->PlayStop(this);
			}
		}

		// Still change the FOV back to the walking one if we are stopped
		ElapsedFOV -= DeltaTime;
		ElapsedFOV = FMath::Max(ElapsedFOV, MinTimeFOV);
	}

	// Update the FOV
	if (IsValid(FOVMultiplierCurve))
	{
		GetFirstPersonCameraComponent()->SetFieldOfView(FOVMultiplierCurve->GetFloatValue(ElapsedFOV) * InititialFOV);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWQCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AWQCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWQCharacter::MoveRight);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AWQCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AWQCharacter::Run);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AWQCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AWQCharacter::LookUpAtRate);

	// Bind power event
	PlayerInputComponent->BindAction("Power", IE_Pressed, this, &AWQCharacter::PowerPressed);
	PlayerInputComponent->BindAction("Power", IE_Released, this, &AWQCharacter::PowerReleased);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AWQCharacter::FirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AWQCharacter::FireReleased);

	// Bind summon event
	PlayerInputComponent->BindAction("Summon", IE_Pressed, this, &AWQCharacter::SummonPressed);
	PlayerInputComponent->BindAction("Summon", IE_Released, this, &AWQCharacter::SummonReleased);

    // Bind misc event
    PlayerInputComponent->BindAction( "Pause", IE_Pressed, this, &AWQCharacter::PauseTriggered ).bExecuteWhenPaused = true;

	//// Bind switching power events
	//PlayerInputComponent->BindAction("SwitchPowerUp", IE_Pressed, this, &AWQCharacter::SwitchPowerUp);
	//PlayerInputComponent->BindAction("SwitchPowerDown", IE_Pressed, this, &AWQCharacter::SwitchPowerDown);
}

/** Power pressed, called by the input */
void AWQCharacter::PowerPressed()
{
	PowerPressedEvent.Broadcast();
}

/** Power released, called by the input */
void AWQCharacter::PowerReleased()
{
	PowerReleasedEvent.Broadcast();
}

/** Fire pressed, called by the input */
void AWQCharacter::FirePressed()
{
	FirePressedEvent.Broadcast();
}

/** Fire released, called by the input */
void AWQCharacter::FireReleased()
{
	FireReleasedEvent.Broadcast();
}

/** Summon pressed, called by the input */
void AWQCharacter::SummonPressed()
{
	SummonPressedEvent.Broadcast();
}

/** Summon released, called by the input */
void AWQCharacter::SummonReleased()
{
	SummonReleasedEvent.Broadcast();
}

/** Switching power with the mouse wheel up, called by the input */
void AWQCharacter::SwitchPowerUp()
{
	Powers[PowerIndex]->SetPowerActive(false);
	PowerIndex = (PowerIndex + 1) % Powers.Num();
	Powers[PowerIndex]->SetPowerActive(true);
}

/** Switching power with the mouse wheel down, called by the input */
void AWQCharacter::SwitchPowerDown()
{
	Powers[PowerIndex]->SetPowerActive(false);
	PowerIndex = (PowerIndex - 1) % Powers.Num();
	Powers[PowerIndex]->SetPowerActive(true);
}

/** Pause behaviour */
void AWQCharacter::PauseTriggered()
{
	UE_LOG(LogTemp, Log, TEXT("Pause has been triggered"));
	if (IsValid(GameInstance))
	{
		GameInstance->PauseManager()->ShowHidePauseMenu();
	}
}

void AWQCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);

		// Try and play the headbob if not jumping specified
		if (!GetCharacterMovement()->IsFalling() && HeadbobShake != nullptr)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(HeadbobShake, GetVelocity().Size() / GetCharacterMovement()->GetMaxSpeed());
		}
	}
}

void AWQCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);

		// Try and play the headbob if not jumping specified
		if (!GetCharacterMovement()->IsFalling() && HeadbobShake != nullptr)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(HeadbobShake, GetVelocity().Size() / GetCharacterMovement()->GetMaxSpeed());
		}
	}
}

/** Handles player run */
void AWQCharacter::Run()
{
	if (bIsRunning)
	{
		bShouldRunInputBeConsumed = false;
		bIsRunning = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		GetCharacterMovement()->MaxAcceleration = WalkingAcceleration;
		HeadbobShake = WalkingHeadbobShake;
	}
	else
	{
		if (GetCharacterMovement()->IsFalling())
		{
			bShouldRunInputBeConsumed = true;
		}
		else
		{
			bShouldRunInputBeConsumed = false;
			bIsRunning = true;
			GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
			GetCharacterMovement()->MaxAcceleration = RunningAcceleration;
			HeadbobShake = RunningHeadbobShake;
		}
	}
}

void AWQCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AWQCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

/** Physic handles management */
UPhysicsHandleComponent* AWQCharacter::GetUnusedPhysicHandle()
{
	if (HandlesUsed >= PhysicHandles.Num())
	{
		AddPhysicHandle(PhysicHandles.Num(), true);
	}

	UPhysicsHandleComponent* PhysicHandle = PhysicHandles[HandlesUsed];
	PhysicHandle->SetActive(true);
	HandlesUsed++;
	return PhysicHandle;
}

/** Clear all physic handle */
void AWQCharacter::ClearAllPhysicHandle()
{
	for (UPhysicsHandleComponent* PhysicHandle : PhysicHandles)
	{
		PhysicHandle->ReleaseComponent();
		PhysicHandle->SetActive(false);
	}
	HandlesUsed = 0;
}

/** Add a physic handle */
void AWQCharacter::AddPhysicHandle(int Index, bool bIsRuntime)
{
	UPhysicsHandleComponent* PhysicHandle;

	if (!bIsRuntime)
	{
		PhysicHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(FName(TEXT("PhysicHandle"), Index));
	}
	else
	{
		PhysicHandle = NewObject<UPhysicsHandleComponent>(this, FName(TEXT("RuntimePhysicHandle"), Index));
		if (PhysicHandle)
		{
			this->AddInstanceComponent(PhysicHandle);
			PhysicHandle->OnComponentCreated();
			PhysicHandle->RegisterComponent();
		}
	}

	if (PhysicHandle)
	{
		PhysicHandle->SetLinearDamping(0.01f);
		PhysicHandle->SetLinearStiffness(1000000000.0f);
		PhysicHandle->SetAngularDamping(0.01f);
		PhysicHandle->SetAngularStiffness(1000000000.0f);
		PhysicHandle->SetInterpolationSpeed(1000000000.0f);
		PhysicHandle->SetActive(false);
		PhysicHandles.Add(PhysicHandle);
	}
}
