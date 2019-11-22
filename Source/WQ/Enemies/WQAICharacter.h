// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UInputComponent;
class AWQAISpawner;

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/ObjectMacros.h"
#include "WQAICharacter.generated.h"

//UENUM( BlueprintType )
//enum class EAIStateEnum : uint8
//{
//    AISE_Unknown UMETA( DisplayName = "Unknown" ),
//    AISE_Alive   UMETA( DisplayName = "Alive" ),
//    AISE_InChase UMETA( DisplayName = "In Chase" ),
//    AISE_Dead    UMETA( DisplayName = "Dead" ),
//};

UCLASS()
class WQ_API AWQAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Sets default values for this character's properties */
	AWQAICharacter();

	/** Called every frame */
	virtual void        Tick(float DeltaTime) override;

	/** Called to bind functionality to input */
	virtual void        SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Getters */
	inline int          GetHealth() const { return HealthPoints; }
	//inline EAIStateEnum GetCurrentState() const { return InstanceState; }

	///** Setters */
	//inline void         TransitionState(const EAIStateEnum nextState) { InstanceState = nextState; }

	/** Damaging interface */
	void				ApplyDamage(const int Damage);

protected:
	/** Called when the game starts or when spawned */
	virtual void        BeginPlay() override;

protected:
	/** Initial health */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI)
	int               InitialHealthPoints;

	/** Track the current information of the AI character */
	UPROPERTY(VisibleAnywhere)
    int                 HealthPoints;

    UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = AI )
    AWQAISpawner*       SpawnOrigin;
};
