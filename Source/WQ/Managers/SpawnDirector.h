// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UUserWidget;

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpawnDirector.generated.h"

/**
 * Manages the pause state and the linked UI
 */
UCLASS(Blueprintable)
class WQ_API USpawnDirector : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = SpawnLogic, meta = ( AllowPrivateAccess = "true" ) )
    int32 NumberHarasser;

public:
    USpawnDirector();
    ~USpawnDirector();
};
