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
#include "Components/SceneComponent.h"
#include "UnrealNetwork.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AWQCharacter

AWQCharacter::AWQCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	//Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	//Mesh1P->SetOnlyOwnerSee(true);
	//Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	//Mesh1P->bCastDynamicShadow = false;
	//Mesh1P->CastShadow = false;
	//Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	//Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	WeaponPivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponPivot"));
	WeaponPivotComponent->SetupAttachment(GetCapsuleComponent());
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(WeaponPivotComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(Mesh1P);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

void AWQCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	Mesh1P->SetHiddenInGame(false, true);
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

	// Bind fire event with parameters
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AWQCharacter::RPCFire);
	//FInputActionHandlerSignature ActionHandler;
	//ActionHandler.BindUFunction(this, TEXT("RPCFire"), GetFirstPersonCameraComponent()->GetComponentRotation());
	//BindActionWithParams(PlayerInputComponent, ActionHandler, TEXT("Fire"));

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
}

void AWQCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(AWQCharacter, WeaponPitch);
}

//void AWQCharacter::BindActionWithParams(UInputComponent* PlayerInputComponent, & Handler, FName ActionName)
//{
//	FInputActionBinding ActionBinding; // Prepare the input binding
//	ActionBinding.ActionName = ActionName; // Getting the input from input settings;
//	ActionBinding.KeyEvent = IE_Pressed; // When pressed
//	ActionBinding.ActionDelegate = Handler; // Connect the delegate with the input
//	PlayerInputComponent->AddActionBinding(ActionBinding); // FInally, add the input
//}

//void AWQCharacter::OnFire()
//{
//	// try and fire a projectile
//	if (ProjectileClass != nullptr)
//	{
//		UWorld* const World = GetWorld();
//		if (World != nullptr)
//		{
//			const FRotator SpawnRotation = GetControlRotation();
//			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
//			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
//
//			//Set Spawn Collision Handling Override
//			FActorSpawnParameters ActorSpawnParams;
//			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
//
//			// spawn the projectile at the muzzle
//			World->SpawnActor<AWQProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
//		}
//	}
//
//	// try and play the sound if specified
//	if (FireSound != nullptr)
//	{
//		//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
//		UWQGameInstance* WQGI = Cast<UWQGameInstance>(GetWorld()->GetGameInstance());
//
//		if (IsValid(WQGI))
//		{
//			WQGI->AudioManager()->PlayTest();
//		}
//	}
//
//	// try and play a firing animation if specified
//	if (FireAnimation != nullptr)
//	{
//		// Get the animation object for the arms mesh
//		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
//		if (AnimInstance != nullptr)
//		{
//			AnimInstance->Montage_Play(FireAnimation, 1.f);
//		}
//	}
//}

// Server implementation
void AWQCharacter::RPCFire_Implementation()
{
	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AWQProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	MulticastRPCFire();
}

void AWQCharacter::RPCFireNetwork_Implementation()
{
	RPCFire();
}

bool AWQCharacter::RPCFireNetwork_Validate()
{
	return true;
}

void AWQCharacter::MulticastRPCFire_Implementation()
{
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		UWQGameInstance* WQGI = Cast<UWQGameInstance>(GetWorld()->GetGameInstance());

		if (IsValid(WQGI))
		{
			WQGI->AudioManager()->PlayTest();
		}
	}

	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AWQCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AWQCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
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
