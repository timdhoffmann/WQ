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
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> btFinder( TEXT( "/Game/Blueprints/Enemies/BT_Pusher" ) );
    static ConstructorHelpers::FObjectFinder<UBlackboardData> bbData( TEXT( "/Game/Blueprints/Enemies/BD_Pusher" ) );

    BehaviorTree = btFinder.Object;

    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>( TEXT( "BlackboardComponent" ) );
    
    UBlackboardData* BlackboardAsset = bbData.Object;

    InitializeBlackboard( *BlackboardComponent, *BlackboardAsset );
    BehaviorTree->BlackboardAsset = BlackboardComponent->GetBlackboardAsset();

    PrimaryActorTick.bCanEverTick = true;
}

void AWQPusherController::BeginPlay()
{
    Super::BeginPlay();

    ForgeTarget = FindObject<AWQAICharacter>( GetLevel(), TEXT( "Forge" ) );
    if ( ensureMsgf(ForgeTarget != nullptr, 
			TEXT("[%s] Could not find a forge to attack in %s. Must belong to the same StreamingLevel and be named 'Forge' in the World Outliner."), 
			*GetName(), 
			*GetLevel()->GetName()
			) 
		) 
	{
        BlackboardComponent->SetValueAsObject( TEXT( "ForgeKey" ), ForgeTarget );
    }
 
    RunBehaviorTree( BehaviorTree );
}

void AWQPusherController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

	if (!ensure(ForgeTarget != nullptr)) return;

    FVector NextActorPosition = ForgeTarget->GetActorLocation();

    AWQAICharacter* character = reinterpret_cast< AWQAICharacter* >( GetCharacter() );
    character->SetActorRotation( UKismetMathLibrary::FindLookAtRotation( character->GetActorLocation(), NextActorPosition ).Quaternion(), ETeleportType::TeleportPhysics );

    BlackboardComponent->SetValueAsObject( TEXT( "ForgeKey" ), ForgeTarget );

    float distanceToForge = FVector::Distance( NextActorPosition, GetCharacter()->GetActorLocation() );

    if ( distanceToForge <= 100.0f ) {
        AWQAICharacter* forgeAi = reinterpret_cast< AWQAICharacter* >( ForgeTarget );
        forgeAi->ApplyDamage( 1 );

        // Crap placeholder
        // TODO SHOULD BE MODIFIED 
        GEngine->AddOnScreenDebugMessage( -1, 9999.0, FColor::Purple, TEXT( "G A M E  O V E R" ), true, FVector2D( 8, 8 ) );

        GetWorld()->ServerTravel( FString( "/Game/_Dev/Baptiste/Maps/MainMenu" ), true );
    }
}
