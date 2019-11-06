// Fill out your copyright notice in the Description page of Project Settings.


#include "Power.h"
#include "WQCharacter.h"

// Sets default values for this component's properties
UPower::UPower()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Identifier = -1;
}


// Called when the game starts
void UPower::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AWQCharacter>(GetOwner());
	if (Character == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("POWER: Character not found!"));
	}
}


// Called every frame
void UPower::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Behaviour when the power is activated
void UPower::SetPowerActive(bool bState)
{
	if (bState)
	{
		// Subscribe to the correct events
		Character->OnPowerPressed().AddUFunction(this, TEXT("PowerPressed"));
		Character->OnPowerReleased().AddUFunction(this, TEXT("PowerReleased"));
	}
	else
	{
		// Unsubscribe
		Character->OnPowerPressed().RemoveAll(this);
		Character->OnPowerReleased().RemoveAll(this);
	}
}

// Behaviour when the power is activated
void UPower::PowerPressed()
{

}

// Behaviour when the power is deactivated
void UPower::PowerReleased()
{

}

