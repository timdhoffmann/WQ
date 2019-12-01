// Fill out your copyright notice in the Description page of Project Settings.

#include "WQGameInstance.h"

#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

#include "AudioManager.h"
#include "EventManager.h"
#include "PauseManager.h"
#include "SpawnDirector.h"
#include "ShakeManager.h"
#include "WQCharacter.h"

UWQGameInstance::UWQGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Constructor."), *GetFullName());
}

void UWQGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Init."), *GetFullName());
}

/** Accessor for C++ & BP */
 // Singleton-like accessor. I only use this as a workaround for PIE
 // The GameInstance lifecycle is different in PIE
 // In proper builds, this wouldn't be necessary
AAudioManager* UWQGameInstance::AudioManager()
{
	if (!IsValid(AudioManagerInstance))
	{
		AudioManagerInstance = GetWorld()->SpawnActor<AAudioManager>(AudioManagerBP);
		AudioManagerInstance->AttachToComponent(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}

	return AudioManagerInstance;
}

/** Accessor for C++ & BP */
UEventManager* UWQGameInstance::EventManager()
{
	return IsValid(EventManagerInstance) ? EventManagerInstance : EventManagerInstance = NewObject<UEventManager>(this, FName("EventManager"));
}

/** Accessor for C++ & BP */
UPauseManager* UWQGameInstance::PauseManager()
{
	if (!IsValid(PauseManagerInstance)) {
		PauseManagerInstance = NewObject<UPauseManager>(this, PauseManagerBP, FName("PauseManager"));
	}

	return PauseManagerInstance;
}

/** Accessor for C++ & BP */
USpawnDirector* UWQGameInstance::SpawnDirector()
{
	if (!IsValid(SpawnDirectorInstance)) {
		SpawnDirectorInstance = NewObject<USpawnDirector>(this, SpawnDirectorBP, FName("SpawnDirector"));
	}

	return SpawnDirectorInstance;
}

/** Accessor for C++ & BP */
UShakeManager* UWQGameInstance::ShakeManager()
{
	if (!IsValid(ShakeManagerInstance)) {
		ShakeManagerInstance = NewObject<UShakeManager>(this, ShakeManagerBP, FName("ShakeManager"));
	}

	return ShakeManagerInstance;
}

void UWQGameInstance::Host() const
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, DefaultMessageDisplaySeconds, FColor::Green, TEXT("Hosting..."));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	/// Travels to new map as a server.
	/// Arguments can be given as part of the Url (listen is required for letting others join).
	World->ServerTravel("/Game/Developers/Tim/Testing_Tim?listen");
}

void UWQGameInstance::Join(FString& IPAddress) const
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, DefaultMessageDisplaySeconds, FColor::Green, FString::Printf(TEXT("Joining %s"), *IPAddress));
}

/** This is where we will clean up, as the game is shut down */
void UWQGameInstance::Shutdown()
{
	// Important, if you overwrite functionality in UE4.
	// Omitting this, may cause errors (depending on the class).
	Super::Shutdown();

	//// PIE may cause this to be invalid. During the game, it will always be valid
	//if (IsValid(AudioManagerInstance))
	//{
	//	// If some behaviour is needed, input it here
	//}
}