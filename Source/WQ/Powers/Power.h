// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Power.generated.h"

/**
 * Base class of all powers (not abstract because of the way Unreal handles things)
 */
UCLASS( ClassGroup=(Power), meta=(BlueprintSpawnableComponent) )
class WQ_API UPower : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPower();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Behaviour when the power is activated
	UFUNCTION(BlueprintCallable, Category = "Power")
	virtual void SetPowerActive(bool bState);

	/** Getter for the identifier */
	virtual int GetIdentifier() const { return Identifier; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Behaviour when the power is activated
	UFUNCTION(BlueprintCallable, Category = "Power")
	virtual void PowerPressed();

	// Behaviour when the power is deactivated
	UFUNCTION(BlueprintCallable, Category = "Power")
	virtual void PowerReleased();

protected:
	// Reference to the character the power is linked to
	UPROPERTY()
	class AWQCharacter* Character;

	/** Identifier to see in which position the power is */
	int Identifier;
};
