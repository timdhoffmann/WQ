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

	/** Sound event of a prop being magnetized */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Powers)
	void PlayPropMagnetized(AActor* Target);

	/** Sound ambiance of a prop while magnetized */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Powers)
	void SetPropMagnetizedAmbiance(bool bState, AActor* Target);

	/** Set the global ambiance active or not */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Environment)
	void SetEnvironmentAmbiance(bool bState);

	/** Change the state of the global ambiance */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Environment)
	void SetEnvironmentState(bool bIsOutside);

	/** Sound event of footsteps */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Character)
	void PlayFootsteps(AActor* Target);

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
