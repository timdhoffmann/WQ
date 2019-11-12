// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UUserWidget;

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PauseManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class WQ_API UPauseManager : public UObject
{
    GENERATED_BODY()

public:
            UPauseManager();
            ~UPauseManager();

    UFUNCTION(BlueprintCallable)
    void    ShowHidePauseMenu();
    
public:
    // The class that will be used for the players Inventory UI
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Player, HUD and UI" )
    TSubclassOf<class UUserWidget> InventoryUIClass;

    // The instance of the players Inventory UI Widget
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Player, HUD and UI" )
    class UUserWidget* InventoryWidget;

private:
    bool bIsPaused;
};
