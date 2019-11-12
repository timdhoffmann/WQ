// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AAudioManager;
class UEventManager;
class UPauseManager;

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WQGameInstance.generated.h"

/**
 * Game Instance, used to manage and reference all managers
 */
UCLASS()
class WQ_API UWQGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Accessors for C++ & BP
	UFUNCTION(BlueprintPure, Category = Managers)
	AAudioManager* AudioManager();
	UFUNCTION(BlueprintPure, Category = Managers)
	UEventManager* EventManager();

    UFUNCTION( BlueprintPure, Category = "Persistence" )
    UPauseManager* PauseManager();

protected:
	// This is where we will clean up, as the game is shut down
	virtual void Shutdown() override;

protected:
	// Needs to be an UPROPERTY(), so the GC does its thing
	// If Transient, it doesn't get serialized itself. Will be nulled when the
	// game starts. Initialization happens later by hand.
	//UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Managers")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Managers")
	TSubclassOf<AAudioManager> AudioManagerBP;

	UPROPERTY()
    AAudioManager* AudioManagerInstance;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Managers" )
    TSubclassOf<UPauseManager> PauseManagerBP;

    UPROPERTY()
    UPauseManager* PauseManagerInstance;

	UPROPERTY()
    UEventManager* EventManagerInstance;
};
