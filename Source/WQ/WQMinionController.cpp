// Fill out your copyright notice in the Description page of Project Settings.


#include "WQMinionController.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void AWQMinionController::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass( GetWorld(), ATargetPoint::StaticClass(), Waypoints );

    GoToRandomWaypoint();
}

ATargetPoint* AWQMinionController::GetRandomWaypoint()
{
    auto index = FMath::RandRange( 0, Waypoints.Num() - 1 );
    return Cast<ATargetPoint>( Waypoints[index] );
}

void AWQMinionController::GoToRandomWaypoint()
{
    MoveToActor( GetRandomWaypoint() );
}
