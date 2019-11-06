// Fill out your copyright notice in the Description page of Project Settings.


#include "WQMinionController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"

#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISense_Sight.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"

#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

#include <limits>

AWQMinionController::AWQMinionController()
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> btFinder( TEXT( "/Game/_Dev/Baptiste/AI/BT_Minion" ) );
    static ConstructorHelpers::FObjectFinder<UBlackboardData> bbData( TEXT( "/Game/_Dev/Baptiste/AI/B_Minion" ) );

    BehaviorTree = btFinder.Object;

    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>( TEXT( "BlackboardComponent" ) );
    BlackboardComponent->InitializeBlackboard( *( bbData.Object ) );

    BehaviorTree->BlackboardAsset = BlackboardComponent->GetBlackboardAsset();

    // Setup the perception component
    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>( TEXT( "AIPerception Component" ) );
    SightConfiguration = CreateDefaultSubobject<UAISenseConfig_Sight>( TEXT( "Sight Config" ) );

    // Configure the Sight Sense of AI Perception
    SightConfiguration->SightRadius = 1000.0f;
    SightConfiguration->LoseSightRadius = 1500.0f;
    SightConfiguration->PeripheralVisionAngleDegrees = 360.0f;
    SightConfiguration->DetectionByAffiliation.bDetectEnemies = true;
    SightConfiguration->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfiguration->DetectionByAffiliation.bDetectFriendlies = true;

    PerceptionComponent->ConfigureSense( *SightConfiguration );
    PerceptionComponent->SetDominantSense( SightConfiguration->GetSenseImplementation() );

    // IMPORTANT : Set the perception component as this one, as the base AIController class has already one !
    // Add a listener to the Perception event, the function needs to be a UFUNCTION !
    PerceptionComponent->OnPerceptionUpdated.AddDynamic( this, &AWQMinionController::OnActorInSight );
    
    SetPerceptionComponent( *PerceptionComponent );

    NextActorToReach = nullptr;
    NextActorPosition = FVector::ZeroVector;
    NextActorDistance = std::numeric_limits<float>::max();

    PrimaryActorTick.bCanEverTick = true; //We won't be ticked by default  
}

void AWQMinionController::BeginPlay()
{
    Super::BeginPlay();

    NextActorToReach = nullptr;
    NextActorPosition = FVector::ZeroVector;
    NextActorDistance = std::numeric_limits<float>::max();

    UGameplayStatics::GetAllActorsOfClass( GetWorld(), ATargetPoint::StaticClass(), Waypoints );
    
    //GoToRandomWaypoint();

    RunBehaviorTree( BehaviorTree );
}

void AWQMinionController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime ); 

    if ( NextActorToReach != nullptr ) {
        BlackboardComponent->SetValueAsVector( TEXT( "MoveToLocationKey" ), NextActorToReach->GetTransform().GetTranslation() );
    }
}

void AWQMinionController::OnActorInSight( const TArray<AActor*>& visibleActors )
{
    FVector minionWorldPosition = RootComponent->GetComponentTransform().GetTranslation();

    NextActorToReach = nullptr;
    NextActorPosition = FVector::ZeroVector;
    NextActorDistance = std::numeric_limits<float>::max();

    GEngine->AddOnScreenDebugMessage( -1, 1.0f, FColor::Yellow, "Iterating visible actors" );
    
    for ( AActor* actor : visibleActors ) {
        FVector actorTranslation = actor->GetTransform().GetTranslation();
        float distanceToMinion = FVector::Distance( actorTranslation, minionWorldPosition );

        if ( distanceToMinion < NextActorDistance ) {
            NextActorToReach = actor;
            NextActorDistance = distanceToMinion;
            NextActorPosition = actorTranslation;
        }
    }

    if ( NextActorToReach != nullptr ) {
        // ty Epic retards...
        FTransform& transform = const_cast<FTransform&>( RootComponent->GetComponentTransform() );
        transform.SetRotation( UKismetMathLibrary::FindLookAtRotation( transform.GetTranslation(), NextActorPosition ).Quaternion() );

        BlackboardComponent->SetValueAsObject( TEXT( "MoveToActorKey" ), NextActorToReach );

        GEngine->AddOnScreenDebugMessage( -1, 1.0f, FColor::Red, "I'm coming for you..." );
    }
}

void AWQMinionController::OnMoveCompleted( FAIRequestID RequestID, const FPathFollowingResult & Result )
{
    Super::OnMoveCompleted( RequestID, Result );

    NextActorToReach = nullptr;
    NextActorPosition = FVector::ZeroVector;
    NextActorDistance = std::numeric_limits<float>::max();
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
