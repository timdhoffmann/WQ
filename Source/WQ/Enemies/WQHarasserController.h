// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionTypes.h"
#include "WQHarasserController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class WQ_API AWQHarasserController : public AAIController
{
	GENERATED_BODY()

public:
    UPROPERTY( EditAnywhere, BlueprintReadWrite )
    UBehaviorTree*          BehaviorTree;

    UPROPERTY( EditAnywhere, BlueprintReadWrite )
    UBlackboardComponent*   BlackboardComponent;

public:
                            AWQHarasserController();

    void                    BeginPlay() override;
    void                    Tick( float DeltaTime ) override;

private:
    AActor*                 ActorTarget;
};
