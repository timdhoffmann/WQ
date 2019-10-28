// Fill out your copyright notice in the Description page of Project Settings.
#include "PauseManager.h"
#include "WQPauseMenu.h"

void UPauseManager::ShowHidePauseMenu()
{
    if ( PauseMenu != nullptr ) {
        if ( PauseMenu->GetIsVisible() == false ) {
            PauseMenu->AddToViewport();
            /*
                        FInputModeGameAndUI Mode;
                        Mode.SetWidgetToFocus( PauseMenu->GetCachedWidget() );*/
           // SetInputMode( Mode );
           // bShowMouseCursor = true;
        } else {
            PauseMenu->RemoveFromViewport();

           // FInputModeGameOnly GameMode;
           //// SetInputMode( GameMode );
           // FSlateApplication::Get().SetUserFocusToGameViewport( 0, EFocusCause::SetDirectly );
          //  bShowMouseCursor = false;
        }
    }
}
