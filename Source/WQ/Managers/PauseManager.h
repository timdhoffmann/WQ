// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PauseManager.generated.h"

/**
 * 
 */
UCLASS()
class WQ_API UPauseManager : public UObject
{
    GENERATED_BODY()

public:
    void ShowHidePauseMenu();

public:
    UPROPERTY()
    UUserWidget* PauseMenu;
};
