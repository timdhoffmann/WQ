// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

UCLASS()
class WQ_API AAudioManager : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties */
	AAudioManager();

	/** Test */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Test")
	void PlayTest();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:	
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

//protected:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
//	UAkAudioEvent* Test;
};
