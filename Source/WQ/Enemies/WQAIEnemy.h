// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/WQAICharacter.h"
#include "WQAIEnemy.generated.h"

/**
 * Base class for all enemies
 */
UCLASS()
class WQ_API AWQAIEnemy : public AWQAICharacter
{
	GENERATED_BODY()
	
public:
    inline void SetTimeDilation( const float dilationFactor ) { CustomTimeDilation = dilationFactor; }

protected:
    /** Max distance between harasser and its target */
    int32       AttackRange;

    /** Move speed during harasser attack */
    int32       DashSpeed;

    /** Time where the harasser is frozen after an attack */
    int32       RecoveryTime;
};
