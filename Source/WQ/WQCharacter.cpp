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
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Powers/Power.h"

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
}

void AWQCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

    UAIPerceptionSystem::RegisterPerceptionStimuliSource( this, UAISense_Sight::StaticClass(), this );
    UAIPerceptionSystem::RegisterPerceptionStimuliSource( this, UAISense_Hearing::StaticClass(), this );

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	Mesh1P->SetHiddenInGame(false, true);

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
}

void AWQCharacter::Tick(float DeltaTime)
{
	// Footsteps logic if the velocity is non null
	if (GetVelocity().SizeSquared() != 0.0f && !bWasJumping)
	{
		bLastFootstepPlayed = false;
		FootstepsStatus += (GetActorLocation() - LastLocation).Size();
		UE_LOG(LogTemp, Log, TEXT("= a %f"), FootstepsStatus);
		LastLocation = GetActorLocation();

		if (FootstepsStatus >= CurrentFootstepsInterval)
		{
			FootstepsStatus = 0.0f;
			UWQGameInstance* WQGI = Cast<UWQGameInstance>(GetGameInstance());
			if (IsValid(WQGI))
			{
				WQGI->AudioManager()->PlayFootsteps(this);
			}
		}
	}
	else if (!bLastFootstepPlayed)
	{
		bLastFootstepPlayed = true;
		FootstepsStatus = 0.0f;
		UWQGameInstance* WQGI = Cast<UWQGameInstance>(GetGameInstance());
		if (IsValid(WQGI))
		{
			WQGI->AudioManager()->PlayStop(this);
		}
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
    UE_LOG( LogTemp, Log, TEXT( "Pause has been triggered" ) )
    reinterpret_cast< UWQGameInstance* >( GetGameInstance() )->PauseManager()->ShowHidePauseMenu();
}

void AWQCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);

		// Try and play the headbob if specified
		if (HeadbobShake != nullptr)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(HeadbobShake, FMath::Abs(Value));
		}
	}
}

void AWQCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);

		// Try and play the headbob if specified
		if (HeadbobShake != nullptr)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(HeadbobShake, FMath::Abs(Value));
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
