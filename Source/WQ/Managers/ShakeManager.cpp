// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakeManager.h"

/** Sets default values */
UShakeManager::UShakeManager()
{
	CurrentPriority = -1;
}

void UShakeManager::PlayHeadbob(bool bIsRunning, float Scale)
{
	FShakeStruct Shake = bIsRunning ? RunningShake : WalkingShake;

	// Only play the shake if it has the correct priority or the last one is over
	if (CurrentPriority > Shake.Priority && IsValid(CurrentShake) && !CurrentShake->IsFinished())
	{
		return;
	}
	else
	{
		CurrentShake = Cast<UCameraShake>(Shake.ShakeBP);
		CurrentPriority = Shake.Priority;
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(Shake.ShakeBP, Scale);
	}	
}

void UShakeManager::PlayBallPropulsion()
{
	// Only play the shake if it has the correct priority or the last one is over
	if (CurrentPriority > BallPropulsionShake.Priority && IsValid(CurrentShake) && !CurrentShake->IsFinished())
	{
		return;
	}
	else
	{
		CurrentShake = Cast<UCameraShake>(BallPropulsionShake.ShakeBP);
		CurrentPriority = BallPropulsionShake.Priority;
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(BallPropulsionShake.ShakeBP);
	}
}

