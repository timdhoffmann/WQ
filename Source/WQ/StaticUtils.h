// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticUtils.generated.h"

/**
 * Static utilities
 */
UCLASS()
class WQ_API UStaticUtils : public UObject
{
	GENERATED_UCLASS_BODY()

	static FVector GetSafeNormal(FVector Vec, float Tolerance = 1.e-8f);
};