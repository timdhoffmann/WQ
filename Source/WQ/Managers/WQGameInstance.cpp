// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioManager.h"
#include "WQGameInstance.h"

 // Singleton-like accessor. I only use this as a workaround for PIE
 // The GameInstance lifecycle is different in PIE
 // In proper builds, this wouldn't be necessary
AAudioManager* UWQGameInstance::AudioManager()
{
	//return IsValid(AudioManagerInstance) ? AudioManagerInstance : AudioManagerInstance = NewObject<AAudioManager>(this, FName("AudioManager"));
	return IsValid(AudioManagerInstance) ? AudioManagerInstance : AudioManagerInstance = GetWorld()->SpawnActor<AAudioManager>(AudioManagerBP);
}

// Cleanup. This acts as a quasi-destructor
void UWQGameInstance::Shutdown()
{
	// Important, if you overwrite functionality in UE4.
	// Omitting this, may cause errors (depending on the class).
	Super::Shutdown();

	// PIE may cause this to be invalid. During the game, it will always be valid
	if (IsValid(AudioManagerInstance))
	{
		// If some behaviour is needed, input it here
	}
}

