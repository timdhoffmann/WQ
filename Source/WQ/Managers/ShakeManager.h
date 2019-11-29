// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ShakeManager.generated.h"

/** Struct to associate shake data */
USTRUCT(BlueprintType)
struct FShakeStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake)
	TSubclassOf<UCameraShake> ShakeBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake)
	int Priority;
};

/**
 * Manages the camera shake of the player
 */
UCLASS(Blueprintable)
class WQ_API UShakeManager : public UObject
{
	GENERATED_BODY()

public:
	/** Constructor */
	UShakeManager();

	/** Shake playing functions */
	void PlayHeadbob(bool bIsRunning, float Scale);
	void PlayBallPropulsion();

protected:
	/** Shake blueprints */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake)
	FShakeStruct WalkingShake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake)
	FShakeStruct RunningShake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake)
	FShakeStruct BallPropulsionShake;

	/** Current shake playing tracking */
	UCameraShake* CurrentShake;
	int CurrentPriority;
};
