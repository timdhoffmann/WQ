// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"

#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("TriggerBox")));
	if (!ensure(TriggerBoxComponent != nullptr)) return;
	SetRootComponent(TriggerBoxComponent);

	TriggerBoxComponent->SetGenerateOverlapEvents(true);
	RegisterDelegates();
}

void APlatformTrigger::RegisterDelegates()
{
	if (!ensure(TriggerBoxComponent != nullptr)) return;
	TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnComponentHasBegunOverlap);
	TriggerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnComponentHasEndedOverlap);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region Delegates
void APlatformTrigger::OnComponentHasBegunOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (auto Platform : Platforms)
	{
		Platform->AddActiveTrigger();
	}
}

void APlatformTrigger::OnComponentHasEndedOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (auto Platform : Platforms)
	{
		Platform->RemoveActiveTrigger();
	}
}
#pragma endregion