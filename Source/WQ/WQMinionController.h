// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WQMinionController.generated.h"

/**
 * 
 */
UCLASS()
class WQ_API AWQMinionController : public AAIController
{
	GENERATED_BODY()

public:
    void BeginPlay() override;

private:
    UPROPERTY()
    TArray<AActor*> Waypoints;

    UFUNCTION()
    ATargetPoint* GetRandomWaypoint();

    UFUNCTION()
    void GoToRandomWaypoint();
};
