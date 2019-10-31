// Fill out your copyright notice in the Description page of Project Settings.


#include "Props.h"
#include "Components/MeshComponent.h"
#include "PropsMovement.h"
#include "WQCharacter.h"

// Sets default values
AProps::AProps()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the movement component
	UPropsMovement* MovementComponent = CreateDefaultSubobject<UPropsMovement>(TEXT("PropsMovementComponent"));
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

/** Move the prop towards a target, make it stop when there is a collision */
void AProps::FlyTowards(float ForceAmplitude, FVector Target)
{
	SetGravitySimulation(false);

	Mesh->AddForce(ForceAmplitude * (Target - GetRootComponent()->GetComponentLocation()));

	Mesh->OnComponentHit.AddDynamic(this, &AProps::StopFly);
}

/** Make the fly stop when there is a collision */
void AProps::StopFly(class UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<class AWQCharacter>(OtherActor) == nullptr)
	{
		//Mesh->OnComponentHit.RemoveAll();

		SetPhysicSimulation(false);
	}
}

