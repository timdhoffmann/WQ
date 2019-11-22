// Fill out your copyright notice in the Description page of Project Settings.


#include "WQAISpawner.h"

// Sets default values
AWQAISpawner::AWQAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWQAISpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWQAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

