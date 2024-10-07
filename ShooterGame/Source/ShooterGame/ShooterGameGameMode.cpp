// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGameGameMode.h"
#include "ShooterGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "UIManager.h"
#include "CharacterManager.h"
#include "Widget/MainHUDWidget.h"
#include "GameFramework/PlayerController.h"

AShooterGameGameMode::AShooterGameGameMode()
{
}

void AShooterGameGameMode::StartPlay()
{
    Super::StartPlay();

    ChangeToGameStartCamera();
    CreateDefaultCharacter();
    CreateMainHUD();
}

void AShooterGameGameMode::CreateMainHUD()
{
    UMainHUDWidget* MainHUDWidget = UUIManager::Instance()->AddWidget<UMainHUDWidget>(this, "WBP_MainHUD");
    if(MainHUDWidget)
    {
        MainHUDWeakPtr = MainHUDWidget;
        MainHUDWidget->OnInit();
        SetInputMode(true);
    }
}

void AShooterGameGameMode::ChangeToGameStartCamera()
{
    TArray<AActor*> Actors;
    UGameplayStatics::GetAllActorsWithTag(this, "StartCamera", Actors);

    if(Actors.Num() > 0)
    {
        AActor* StartCamera = Actors[0];
        if(StartCamera)
        {   
            APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
            if(CameraManager)
            {
                CameraManager->SetViewTarget(StartCamera);
            }
        }
    }
}

void AShooterGameGameMode::CreateDefaultCharacter()
{
    // Create Default Character Wiraith
    UCharacterManager::Instance()->SetCharacter(1000);
}

void AShooterGameGameMode::SetInputMode(bool bOnlyUIMode)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if(PlayerController)
    {
        // FInputModeUIOnly InputMode;
        PlayerController->SetInputMode(FInputModeUIOnly());
        PlayerController->bShowMouseCursor = true;
        
    }
}
