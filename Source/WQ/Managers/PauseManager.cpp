// Fill out your copyright notice in the Description page of Project Settings.
#include "PauseManager.h"
#include "WQPauseMenu.h"

#include "Engine/Classes/GameFramework/Character.h"
#include "Engine/Classes/GameFramework/PlayerController.h"

#include "Engine/Classes/Kismet/GameplayStatics.h"

/** Constructor */
UPauseManager::UPauseManager()
    : bIsPaused( false )
    , InventoryWidget( nullptr )
{
    static ConstructorHelpers::FClassFinder<UUserWidget> UMGClassFinder( TEXT( "Class'/Game/_Dev/Baptiste/Blueprints/UI/PauseMenu.PauseMenu_C'" ) );
    if ( UMGClassFinder.Class ) {
        InventoryUIClass = UMGClassFinder.Class;
    } else {
        UE_LOG( LogTemp, Warning, TEXT( "Error: Pause UMG not found" ) );
    }
}

/** Destructor */
UPauseManager::~UPauseManager()
{
    if ( InventoryWidget != nullptr ) {
        InventoryWidget->SetVisibility( ESlateVisibility::Hidden ); // Set it to hidden so its not open on spawn.
        InventoryWidget->RemoveFromViewport();
        InventoryWidget = nullptr;
    }

    bIsPaused = false;
}

/** Used to show or hide the pause menu UI */
void UPauseManager::ShowHidePauseMenu()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if ( InventoryWidget == nullptr ) {
        InventoryWidget = CreateWidget<UUserWidget>( PlayerController, InventoryUIClass ); // Create Widget

        InventoryWidget->AddToViewport(); // Add it to the viewport so the Construct() method in the UUserWidget:: is run.
        InventoryWidget->SetVisibility( ESlateVisibility::Hidden ); // Set it to hidden so its not open on spawn.
    }

    bIsPaused = !bIsPaused;

    //if ( bIsPaused ) {
    //    FInputModeUIOnly InputModeData;
    //    InputModeData.SetWidgetToFocus( InventoryWidget->TakeWidget() );
    //    InputModeData.SetLockMouseToViewportBehavior( EMouseLockMode::DoNotLock );
    //    PlayerController->SetInputMode( InputModeData );
    //}

    PlayerController->bShowMouseCursor = bIsPaused;
    InventoryWidget->SetVisibility( ( bIsPaused ) ? ESlateVisibility::Visible : ESlateVisibility::Hidden );

    UGameplayStatics::SetGamePaused( GWorld, bIsPaused );
}
