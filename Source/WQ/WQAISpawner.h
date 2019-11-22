// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WQAISpawner.generated.h"

UCLASS()
class WQ_API AWQAISpawner : public AActor
{
	GENERATED_BODY()

public:
    inline void DecrementSpawnTickets() { NumberHarasser--; }

public:	
	// Sets default values for this actor's properties
	AWQAISpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = Movement, meta = ( AllowPrivateAccess = "true" ) )
    int32 NumberHarasser;
};
