// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/ObjectMacros.h"
#include "WQAICharacter.generated.h"

UENUM( BlueprintType )
enum class EAIStateEnum : uint8
{
    AISE_Unknown UMETA( DisplayName = "Unknown" ),
    AISE_Alive   UMETA( DisplayName = "Alive" ),
    AISE_InChase UMETA( DisplayName = "In Chase" ),
    AISE_Dead    UMETA( DisplayName = "Dead" ),
};

UCLASS()
class WQ_API AWQAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
    UPROPERTY( EditAnywhere )
    float               InitialHealthPoint;

    UPROPERTY( EditAnywhere )
    EAIStateEnum           InitialState;

public:
    inline float        GetHealth() const                               { return HealthPoint; }
    inline EAIStateEnum GetCurrentState() const                         { return InstanceState; }

    inline void         ApplyDamages( const float damages )             { HealthPoint -= damages; }
    inline void         TransitionState( const EAIStateEnum nextState ) { InstanceState = nextState; }

public:
	                    // Sets default values for this character's properties
	                    AWQAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void        BeginPlay() override;

public:	
	// Called every frame
	virtual void        Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void        SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    float               HealthPoint;
    EAIStateEnum        InstanceState;
};
