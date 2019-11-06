// Fill out your copyright notice in the Description page of Project Settings.


#include "Props.h"
#include "Components/MeshComponent.h"
#include "PropsMovement.h"
#include "WQCharacter.h"
#include "StaticUtils.h"

// Sets default values
AProps::AProps()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the movement component
	PropsMovementComponent = CreateDefaultSubobject<UPropsMovement>(TEXT("PropsMovementComponent"));

	// Default values
	bIsFlying = false;
}

// Called when the game starts or when spawned
void AProps::BeginPlay()
{
	Super::BeginPlay();

	SetPhysicSimulation(true);
}

// Called every frame
void AProps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AProps::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/** Changes the simulation physics status */
void AProps::SetPhysicSimulation(bool bState)
{
	if (Mesh != nullptr)
	{
		Mesh->SetSimulatePhysics(bState);
		if (bState)
		{
			Mesh->WakeAllRigidBodies();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Props: MESH NOT DEFINED!"));
	}
}

/** Changes the gravity physics status */
void AProps::SetGravitySimulation(bool bState)
{
	if (Mesh != nullptr)
	{
		Mesh->SetEnableGravity(bState);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Props: MESH NOT DEFINED!"));
	}
}

/** Remove physical sims, move the prop towards a target */
void AProps::FlyTowards(FVector Target, float Speed)
{
	//SetPhysicSimulation(false);
	//GetRootComponent()->AttachToComponent(NewParent, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	//PropsMovementComponent->MoveAutomaticallyTo(NewParent, Speed, MagnetizationRadius);
	SetGravitySimulation(false);
	Mesh->AddForce(UStaticUtils::GetSafeNormal(Target - GetRootComponent()->GetComponentLocation()) * Speed, NAME_None, true);
	Mesh->SetCollisionProfileName(TEXT("PropsHeld"));
}

/** Stop the flying */
void AProps::FlyStop()
{
	//DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//SetPhysicSimulation(true);
	//PropsMovementComponent->StopAutomaticMovement();
	Mesh->SetCollisionProfileName(TEXT("Props"));
	SetGravitySimulation(true);
}

/** Propulse physically */
void AProps::Propulse(FVector Direction, float Strength)
{
	Mesh->AddForce(Direction * Strength * Mesh->GetMassScale(), NAME_None, true);
}

