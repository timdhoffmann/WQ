// Fill out your copyright notice in the Description page of Project Settings.


#include "WQPusherController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"

#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISense_Sight.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"

#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"

#include <limits>

#include "Enemies/WQAICharacter.h"

AWQPusherController::AWQPusherController()
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> btFinder( TEXT( "/Game/_Dev/Baptiste/AI/BT_Minion" ) );
    static ConstructorHelpers::FObjectFinder<UBlackboardData> bbData( TEXT( "/Game/_Dev/Baptiste/AI/B_Minion" ) );

    BehaviorTree = btFinder.Object;

    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>( TEXT( "BlackboardComponent" ) );
    
    UBlackboardData* BlackboardAsset = bbData.Object;

    InitializeBlackboard( *BlackboardComponent, *BlackboardAsset );
    BehaviorTree->BlackboardAsset = BlackboardComponent->GetBlackboardAsset();
}

void AWQPusherController::BeginPlay()
{
    Super::BeginPlay();

    AActor* ForgeTarget = FindObject<AWQAICharacter>( GetLevel(), TEXT( "Forge" ) );

    if ( ForgeTarget != nullptr ) {
        BlackboardComponent->SetValueAsObject( TEXT( "ForgeKey" ), ForgeTarget );
    }
 
    RunBehaviorTree( BehaviorTree );
}
