// Fill out your copyright notice in the Description page of Project Settings.


#include "WQMinionController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"

AWQMinionController::AWQMinionController()
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> btFinder( TEXT( "/Game/_Dev/Baptiste/AI/BT_Minion" ) );
    static ConstructorHelpers::FObjectFinder<UBlackboardData> bbData( TEXT( "/Game/_Dev/Baptiste/AI/B_Minion" ) );

    BehaviorTree = btFinder.Object;

    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>( TEXT( "BlackboardComponent" ) );
    BlackboardComponent->InitializeBlackboard( *( bbData.Object ) );

    BehaviorTree->BlackboardAsset = BlackboardComponent->GetBlackboardAsset();
}

void AWQMinionController::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass( GetWorld(), ATargetPoint::StaticClass(), Waypoints );
    
    GoToRandomWaypoint();

    RunBehaviorTree( BehaviorTree );
}

void AWQMinionController::OnMoveCompleted( FAIRequestID RequestID, const FPathFollowingResult & Result )
{
    Super::OnMoveCompleted( RequestID, Result );

    GetWorldTimerManager().SetTimer( TimerHandle, this, &AWQMinionController::GoToRandomWaypoint, 0.10f, true );
}

ATargetPoint* AWQMinionController::GetRandomWaypoint()
{
    int64 index = FMath::RandRange( 0, Waypoints.Num() - 1 );
    return Cast<ATargetPoint>( Waypoints[index] );
}

void AWQMinionController::GoToRandomWaypoint()
{
    ATargetPoint* waypoint = GetRandomWaypoint();
    FVector pointTranslation = waypoint->GetTransform().GetTranslation();
    BlackboardComponent->SetValueAsVector( TEXT( "MoveToLocationKey" ), pointTranslation );
}
