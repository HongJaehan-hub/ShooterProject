// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterManager.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "Dom/JsonObject.h"
#include "GameFramework/Pawn.h"
#include "CMSTable.h"
#include "GameFramework/PlayerStart.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Engine/GameInstance.h"
#include "Engine/EngineTypes.h"
#include "ShooterGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "ResourceManager.h"

UCharacterManager* UCharacterManager::_Instance = nullptr;

UCharacterManager *UCharacterManager::Instance()
{
    if(_Instance == nullptr)
    {
        _Instance = NewObject<UCharacterManager>();
        _Instance->AddToRoot(); // GC 방지
    }
    return _Instance;
}

void UCharacterManager::Init(UGameInstance* ShooterGameInstance)
{
    CurrentCharacterId = 0;
    CachedPawn.Reset();
    GameInstance = ShooterGameInstance;
    CachedPlayerStart = nullptr;
}

void UCharacterManager::Destroyed()
{
    CachedPlayerStart = nullptr;
}

void UCharacterManager::SetCharacter(int32 CharacterId)
{
    if(CurrentCharacterId == CharacterId)
        return;

    // 기존 Pawn 숨김 처리
    HideAllCharacters();
    CurrentCharacterId = CharacterId;

    // 캐싱된 데이터가 있으면 해당 Pawn 사용
    if(CachedPawn.Num() != 0 && CachedPawn.Contains(CharacterId))
    {
        APawn* Pawn = CachedPawn[CharacterId];
        if(Pawn)
        {
            Pawn->SetActorHiddenInGame(false);
            CurrentPawn = Pawn;
            return;
        }
    }

    // 캐릭터 생성
    APawn* SpawnedPawn = SpawnCharacter(CharacterId);
    if(SpawnedPawn)
    {
        CurrentPawn = SpawnedPawn;
        CachedPawn.Add(CharacterId, CurrentPawn);
    }
}

APawn* UCharacterManager::SpawnCharacter(int32 CharacterId)
{
    // Character Table에서 Asset 정보를 가져와 Spawn
    TSharedPtr<FJsonObject> CharacterCms = UCMSTable::Instance()->GetTableRow("Character", CharacterId);
    if(CharacterCms.IsValid())
    {  
        FString AssetName = CharacterCms->GetStringField(TEXT("CharacterAsset"));
        FString AssetClassPath = UResourceManager::Instance()->GetAssetClassPath(AssetName);
        UE_LOG(LogTemp, Warning, TEXT("AssetClassPath : %s"), *AssetClassPath);

        FSoftObjectPath SoftObjectPath(AssetClassPath);
        UClass* NewCharacterClass = Cast<UClass>(SoftObjectPath.TryLoad());
        if(NewCharacterClass)
        {
            APlayerStart* PlayerStart = GetPlayerStart();
            if(PlayerStart)
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                return GameInstance->GetWorld()->SpawnActor<APawn>(NewCharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParams);
            }
        }
    }
    return nullptr;
}

void UCharacterManager::HideAllCharacters()
{
    if(CachedPawn.Num() == 0)
        return;

    for(const auto& Pair : CachedPawn)
    {
        APawn* Pawn = Pair.Value;
        if(Pawn)
        {
            Pawn->SetActorHiddenInGame(true);
        }
    }
}

void UCharacterManager::PossessCurrentCharacter()
{
    auto PlayerController = GameInstance->GetWorld()->GetFirstPlayerController();
    if(PlayerController && CurrentPawn)
    {
        // PlayerController->Possess(CurrentPawn);
        PlayerController->SetViewTargetWithBlend(CurrentPawn, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
        // Calls Possess after the camera blend complete
        FTimerHandle TimerHandle;
        GameInstance->GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([PlayerController = PlayerController, CurrentPawn = CurrentPawn]()
        {
            PlayerController->Possess(CurrentPawn);
        }), CameraBlendTime, false);
    }
}

int32 UCharacterManager::GetCurrentCharacterId()
{
    return CurrentCharacterId;
}

APlayerStart* UCharacterManager::GetPlayerStart()
{
    if(CachedPlayerStart != nullptr)
        return CachedPlayerStart;
    
    UWorld* World = GameInstance->GetWorld();
    if(World)
    {
        for(TActorIterator<APlayerStart> It(World); It; ++It)
        {
            CachedPlayerStart = *It;
            return CachedPlayerStart;
        }
    }
    return nullptr;
}
