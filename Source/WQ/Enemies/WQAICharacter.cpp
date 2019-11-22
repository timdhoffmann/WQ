// Fill out your copyright notice in the Description page of Project Settings.
#include "WQAICharacter.h"
#include "WQAISpawner.h"

/** Sets default values */
AWQAICharacter::AWQAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default values
    SpawnOrigin = nullptr;
	InitialHealthPoints = 1;
}

/** Called when the game starts or when spawned */
void AWQAICharacter::BeginPlay()
{
	Super::BeginPlay();

    HealthPoints     = InitialHealthPoints;
    //InstanceState   = InitialState;
}

/** Called every frame */
void AWQAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    //if ( HealthPoint <= 0.0f ) {
    //    InstanceState = EAIStateEnum::AISE_Dead;
    //}

    //if ( InstanceState == EAIStateEnum::AISE_Dead ) {
    //    // TODO This is kinda caca atm
    //    // Still need to add animation/sfx/vfx to make this prettier
    //    Destroy();
    //}
}

/** Called to bind functionality to input */
void AWQAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/** Damaging interface */
void AWQAICharacter::ApplyDamage(const int Damage)
{
	HealthPoints -= Damage;
    
	if (HealthPoints <= 0)
	{
        // If the current AI character has been spawned from a spawner, notify its death in order to update the spawner ticket count
        if ( SpawnOrigin != nullptr ) {
            SpawnOrigin->DecrementSpawnTickets();
        }

		// TODO: Death logic
		this->Destroy();
	}
}