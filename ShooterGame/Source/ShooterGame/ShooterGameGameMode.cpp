// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGameGameMode.h"
#include "ShooterGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "UIManager.h"
#include "Widget/MainHUDWidget.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "CMSTable.h"

AShooterGameGameMode::AShooterGameGameMode()
{
}

void AShooterGameGameMode::StartPlay()
{
    Super::StartPlay();

    CreateMainHUD();
    ChangeToGameStartCamera();
    CreateDefaultCharacter();
}

void AShooterGameGameMode::CreateMainHUD()
{
    UMainHUDWidget* MainHUDwidget = UUIManager::Instance()->AddWidget<UMainHUDWidget>(this, "WBP_MainHUD");
    if(MainHUDwidget)
    {
        MainHUDwidget->OnInit();
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
    FString CharacterName = "Revenant";
    FString BpPreName = "BP_Character_";
    FString FullName = BpPreName + CharacterName;
    FString Path = "/Game/Shooter/Blueprints/Characters/" + FullName + "." + FullName + "_C";

    FSoftObjectPath SoftObjectPath(Path);
    UClass* NewCharacterClass = Cast<UClass>(SoftObjectPath.TryLoad());
    if(NewCharacterClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Success class"));
        APlayerStart* PlayerStart = GetPlayerStart();
        if(PlayerStart)
        {
            APawn* Pawn = GetWorld()->SpawnActor<APawn>(NewCharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());
            if(Pawn)
            {
                auto PlayerController = GetWorld()->GetFirstPlayerController();
                if(PlayerController)
                {
                    // PlayerController->Possess(Pawn);
                    PlayerController->SetViewTargetWithBlend(Pawn, 10.0f, EViewTargetBlendFunction::VTBlend_Cubic);
                }
            }
        }
    }

    TSharedPtr<FJsonObject> JsonObject = UCMSTable::Instance()->GetTableRow("Character", 1);
    if(JsonObject.IsValid())
    {
        int32 Id = JsonObject->GetNumberField(TEXT("Id"));
        FString Name = JsonObject->GetStringField(TEXT("Name"));
    }
}

APlayerStart* AShooterGameGameMode::GetPlayerStart()
{
    UWorld* World = GetWorld();
    if(World)
    {
        for(TActorIterator<APlayerStart> It(World); It; ++It)
        {
            return *It;
        }
    }
    return nullptr;
}
