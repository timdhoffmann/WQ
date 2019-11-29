// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UUserWidget;

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PauseManager.generated.h"

/**
 * Manages the pause state and the linked UI
 */
UCLASS(Blueprintable)
class WQ_API UPauseManager : public UObject
{
    GENERATED_BODY()

public:
            UPauseManager();
            ~UPauseManager();

	/** Used to show or hide the pause menu UI */
    UFUNCTION(BlueprintCallable, Category = Pause)
    void    ShowHidePauseMenu();
    
protected:
    /** The class that will be used for the players Inventory UI */
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Pause )
    TSubclassOf<class UUserWidget> InventoryUIClass;

    /** The instance of the players Inventory UI Widget */
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Pause )
    class UUserWidget* InventoryWidget;

private:
	/** Is the game paused ? */
    bool bIsPaused;
};
