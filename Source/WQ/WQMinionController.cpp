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

#include "Enemies/WQAICharacter.h"

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

    // Configure the Sight Sense of AI Perception
    UAISenseConfig_Sight* SightConfiguration = CreateDefaultSubobject<UAISenseConfig_Sight>( TEXT( "Sight Config" ) );
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
    NextActorDistance = std::numeric_limits<float>::max();

    // TODO Investigate if 3D AI Sight worth a try?
    // Right now, the plugin API is crappy and doesnt work w/ Actor targets...
    PrimaryActorTick.bCanEverTick = true; //We won't be ticked by default  
}

void AWQMinionController::BeginPlay()
{
    Super::BeginPlay();

    NextActorToReach = nullptr;
    NextActorPosition = FVector::ZeroVector;
    NextActorDistance = std::numeric_limits<float>::max();

    RunBehaviorTree( BehaviorTree );
}

void AWQMinionController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime ); 

    AWQAICharacter* character = reinterpret_cast< AWQAICharacter* >( GetCharacter() );

/* 
    // HP API Test stuff
    character->ApplyDamages( 1.0f );
    GEngine->AddOnScreenDebugMessage( -1, 1.0f, FColor::Red, FString( "HP: " + FString::SanitizeFloat( character->GetHealth() ) ) );
*/

    if ( NextActorToReach != nullptr ) {
        NextActorPosition = NextActorToReach->GetActorLocation();

        character->SetActorRotation( UKismetMathLibrary::FindLookAtRotation( character->GetActorLocation(), NextActorPosition ).Quaternion() );

        BlackboardComponent->SetValueAsVector( TEXT( "MoveToLocationKey" ), NextActorPosition );
    }
}

void AWQMinionController::OnActorInSight( const TArray<AActor*>& visibleActors )
{
    AWQAICharacter* character = reinterpret_cast< AWQAICharacter* >( GetCharacter() );
    const FVector minionWorldPosition = character->GetActorLocation();

    NextActorToReach = nullptr;
    NextActorPosition = FVector::ZeroVector;
    NextActorDistance = std::numeric_limits<float>::max();

    for ( AActor* actor : visibleActors ) {
        FVector actorTranslation = actor->GetActorLocation();
        float distanceToMinion = FVector::Distance( actorTranslation, minionWorldPosition );

        if ( distanceToMinion < NextActorDistance ) {
            NextActorToReach = actor;
            NextActorDistance = distanceToMinion;
            NextActorPosition = actorTranslation;
        }
    }

    if ( NextActorToReach != nullptr ) {
        character->SetActorRotation( UKismetMathLibrary::FindLookAtRotation( character->GetActorLocation(), NextActorPosition ).Quaternion() );
        character->TransitionState( EAIStateEnum::AISE_InChase );

        BlackboardComponent->SetValueAsObject( TEXT( "MoveToActorKey" ), NextActorToReach );
    } else {
        character->TransitionState( EAIStateEnum::AISE_Alive );
    }
}
