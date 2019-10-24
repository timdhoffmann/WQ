// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WQGameMode.h"
#include "WQHUD.h"
#include "WQCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWQGameMode::AWQGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/_Project/Blueprints/Character/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AWQHUD::StaticClass();
}
