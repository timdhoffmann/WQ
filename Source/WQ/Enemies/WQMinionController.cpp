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
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"

#include <limits>

#include "Enemies/WQAICharacter.h"

AWQMinionController::AWQMinionController()
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> btFinder( TEXT( "/Game/_Dev/Baptiste/AI/BT_Minion" ) );
    static ConstructorHelpers::FObjectFinder<UBlackboardData> bbData( TEXT( "/Game/_Dev/Baptiste/AI/B_Minion" ) );

    BehaviorTree = btFinder.Object;

    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>( TEXT( "BlackboardComponent" ) );
    
    UBlackboardData* BlackboardAsset = bbData.Object;
    /* UBlackboardData* BlackboardAssetCp = NewObject< UBlackboardData >( BlackboardComponent );
     BlackboardAssetCp->UpdatePersistentKey<UObject>( FName( "MoveToActorKey" ) );
     BlackboardAssetCp->UpdatePersistentKey<UObject>( FName( "SelfActor" ) );*/

    //UBlackboardData* bbData2 = NewObject<UBlackboardData>( BlackboardComponent );
    //*bbData2 = *( (UBlackboardData*)bbData.Object );

    InitializeBlackboard( *BlackboardComponent, *BlackboardAsset );
    BehaviorTree->BlackboardAsset = BlackboardComponent->GetBlackboardAsset();

    // Setup the perception component
    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>( TEXT( "AIPerception Component" ) );

    // Configure the Sight Sense of AI Perception
    UAISenseConfig_Sight* SightConfiguration = CreateDefaultSubobject<UAISenseConfig_Sight>( TEXT( "Sight Config" ) );
    SightConfiguration->SightRadius = 1500.0f;
    SightConfiguration->LoseSightRadius = 2000.0f;
    SightConfiguration->PeripheralVisionAngleDegrees = 360.0f;
    SightConfiguration->DetectionByAffiliation.bDetectEnemies = true;
    SightConfiguration->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfiguration->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfiguration->AutoSuccessRangeFromLastSeenLocation = 15000.0f;

    SightConfiguration->SetMaxAge( 3000000.0f );

    PerceptionComponent->ConfigureSense( *SightConfiguration );
    PerceptionComponent->SetDominantSense( SightConfiguration->GetSenseImplementation() );

    // IMPORTANT : Set the perception component as this one, as the base AIController class has already one !
    // Add a listener to the Perception event, the function needs to be a UFUNCTION !
    PerceptionComponent->OnPerceptionUpdated.AddUniqueDynamic( this, &AWQMinionController::OnActorInSight );
    
    SetPerceptionComponent( *PerceptionComponent );

    BlackboardComponent->SetValueAsObject( TEXT( "SelfActor" ), this );

    NextActorToReach = nullptr;
    NextActorDistance = std::numeric_limits<float>::max();

    // TODO Investigate if 3D AI Sight worth a try?
    // Right now, the plugin API is crappy and doesnt work w/ Actor targets...
    PrimaryActorTick.bCanEverTick = true; // true; //We won't be ticked by default  
}

void AWQMinionController::BeginPlay()
{
    Super::BeginPlay();

    NextActorToReach = nullptr;
    NextActorPosition = FVector::ZeroVector;
    NextActorDistance = std::numeric_limits<float>::max();

    AActor* ForgeTarget = FindObject<AWQAICharacter>( GetLevel(), TEXT( "Forge" ) );

    if ( ForgeTarget != nullptr ) {
        NextActorToReach = ForgeTarget;
        BlackboardComponent->SetValueAsObject( TEXT( "MoveToActorKey" ), NextActorToReach );
    }
 
    RunBehaviorTree( BehaviorTree );
}

void AWQMinionController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime ); 

    if ( NextActorToReach != nullptr ) {
        NextActorPosition = NextActorToReach->GetActorLocation();

        AWQAICharacter* character = reinterpret_cast< AWQAICharacter* >( GetCharacter() );
        character->SetActorRotation( UKismetMathLibrary::FindLookAtRotation( character->GetActorLocation(), NextActorPosition ).Quaternion(), ETeleportType::TeleportPhysics );

        BlackboardComponent->SetValueAsVector( TEXT( "MoveToLocationKey" ), NextActorPosition );
        BlackboardComponent->SetValueAsObject( TEXT( "MoveToActorKey" ), NextActorToReach );
    }
}

void AWQMinionController::OnActorInSight( const TArray<AActor*>& visibleActors )
{
    AWQAICharacter* character = reinterpret_cast< AWQAICharacter* >( GetCharacter() );
    const FVector minionWorldPosition = character->GetActorLocation();
    /*
        NextActorToReach = nullptr;
        NextActorPosition = FVector::ZeroVector;
        NextActorDistance = std::numeric_limits<float>::max();
    */
    for ( AActor* actor : visibleActors ) {
        FVector actorTranslation = actor->GetActorLocation();
        float distanceToMinion = FVector::Distance( actorTranslation, minionWorldPosition );
        
        FString objName;
        actor->GetName( objName );
        if ( objName == "FirstPersonCharacter2" || actor->ActorHasTag( "Player" ) ) {
            GEngine->AddOnScreenDebugMessage( -1, 1.0f, FColor::Red, FString( "GO TO PLAYER!" ) );
            NextActorToReach = actor;
            NextActorDistance = distanceToMinion;
            NextActorPosition = actorTranslation;
            character->SetActorRotation( UKismetMathLibrary::FindLookAtRotation( character->GetActorLocation(), NextActorPosition ).Quaternion(), ETeleportType::TeleportPhysics );
          
            BlackboardComponent->SetValueAsObject( TEXT( "MoveToActorKey" ), NextActorToReach );
            return;
        }
    }

    AActor* ForgeTarget = FindObject<AWQAICharacter>( GetLevel(), TEXT( "Forge" ) );
    if ( ForgeTarget != nullptr ) {
        GEngine->AddOnScreenDebugMessage( -1, 1.0f, FColor::Yellow, FString( "GO TO FORGE!" ) );
        NextActorToReach = ForgeTarget;
        character->SetActorRotation( UKismetMathLibrary::FindLookAtRotation( character->GetActorLocation(), ForgeTarget->GetActorLocation() ).Quaternion(), ETeleportType::TeleportPhysics );
        
        BlackboardComponent->SetValueAsObject( TEXT( "MoveToActorKey" ), NextActorToReach );
    }
}
