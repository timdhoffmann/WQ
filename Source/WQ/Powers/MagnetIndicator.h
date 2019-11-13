// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagnetIndicator.generated.h"

UCLASS()
class WQ_API AMagnetIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties */
	AMagnetIndicator();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Function made to enable/disable the actor */
	void SetActorActive(bool bState);

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

protected:
	/** All actor components */
	UPROPERTY()
	TArray<USceneComponent*> Components;
};
