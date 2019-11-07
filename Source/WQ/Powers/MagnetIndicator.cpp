// Fill out your copyright notice in the Description page of Project Settings.


#include "MagnetIndicator.h"

// Sets default values
AMagnetIndicator::AMagnetIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMagnetIndicator::BeginPlay()
{
	Super::BeginPlay();

	// Get all actor components here
	GetComponents<USceneComponent>(Components);

	// Start deactivated
	SetActorActive(false);
}

// Called every frame
void AMagnetIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/** Function made to enable/disable the actor */
void AMagnetIndicator::SetActorActive(bool bState)
{
	for (USceneComponent* Component : Components)
	{
		Component->SetHiddenInGame(!bState, true);
	}
}

