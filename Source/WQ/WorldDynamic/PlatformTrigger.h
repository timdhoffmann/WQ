// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformTrigger.generated.h"

#pragma region Forward Declarations
class AMovingPlatform;
class UBoxComponent;
#pragma endregion

UCLASS()
class WQ_API APlatformTrigger : public AActor
{
	GENERATED_BODY()

#pragma region Variables
private:
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TriggerBoxComponent = nullptr;

#pragma endregion

#pragma region Functions
public:
	// Sets default values for this actor's properties
	APlatformTrigger();
	void RegisterDelegates();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	/* The platforms to trigger. */
	UPROPERTY(EditAnywhere, Category = "Setup")
		TArray<AMovingPlatform*> Platforms;

#pragma region Delegates
	/// Must be UFUNCTIONs!

	UFUNCTION()
		void OnComponentHasBegunOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentHasEndedOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
#pragma endregion
#pragma endregion
};
