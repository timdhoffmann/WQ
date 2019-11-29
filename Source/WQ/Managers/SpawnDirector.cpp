// Fill out your copyright notice in the Description page of Project Settings.
#include "SpawnDirector.h"

/** Constructor */
USpawnDirector::USpawnDirector()
{
    NumberHarasser = 0;
}

/** Destructor */
USpawnDirector::~USpawnDirector()
{
	
}

bool USpawnDirector::IsSpawnerSuitable( const USphereComponent* spawnArea )
{
    return true;
    /*FVector actorLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    return FVector::Dist( actorLocation, spawnArea->GetComponentLocation() ) > spawnArea->GetScaledSphereRadius();*/
}