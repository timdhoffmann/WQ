// Fill out your copyright notice in the Description page of Project Settings.


#include "WQHarasserController.h"

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
#include "WQ/WQCharacter.h"

AWQHarasserController::AWQHarasserController()
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> btFinder( TEXT( "/Game/Blueprints/Enemies/BT_Harasser" ) );
    static ConstructorHelpers::FObjectFinder<UBlackboardData> bbData( TEXT( "/Game/Blueprints/Enemies/BD_Harasser" ) );

    BehaviorTree = btFinder.Object;

    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>( TEXT( "BlackboardComponent" ) );

    UBlackboardData* BlackboardAsset = bbData.Object;
    InitializeBlackboard( *BlackboardComponent, *BlackboardAsset );
    BehaviorTree->BlackboardAsset = BlackboardComponent->GetBlackboardAsset();

    BlackboardComponent->SetValueAsObject( TEXT( "SelfActor" ), this );

    PrimaryActorTick.bCanEverTick = true; // true; //We won't be ticked by default  
}

void AWQHarasserController::BeginPlay()
{
    Super::BeginPlay();

    ActorTarget = FindObject<AWQCharacter>( GetLevel(), TEXT( "FirstPersonCharacter2" ) );
    BlackboardComponent->SetValueAsObject( TEXT( "PlayerKey" ), ActorTarget );

    RunBehaviorTree( BehaviorTree );
}

void AWQHarasserController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

    FVector NextActorPosition = ActorTarget->GetActorLocation();

    AWQCharacter* character = reinterpret_cast< AWQCharacter* >( GetCharacter() );
    character->SetActorRotation( 
        UKismetMathLibrary::FindLookAtRotation( character->GetActorLocation(), NextActorPosition ).Quaternion(), 
        ETeleportType::TeleportPhysics );

    BlackboardComponent->SetValueAsObject( TEXT( "PlayerKey" ), ActorTarget );
}
