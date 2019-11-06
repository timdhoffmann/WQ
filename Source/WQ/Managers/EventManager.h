// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventManager.generated.h"

DECLARE_DELEGATE(FSimpleCallback);

/**
 * Event manager, globally accessible through the Game Instance
 */
UCLASS()
class WQ_API UEventManager : public UObject
{
	GENERATED_BODY()

//public:
//	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Powers)
//	FGeneralNoParam OnRescalingFinished;
};
