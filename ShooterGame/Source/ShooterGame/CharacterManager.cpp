// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterManager.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "Dom/JsonObject.h"

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

void UCharacterManager::Init()
{
    // FString FilePath = FPaths::ProjectContentDir() / TEXT("Shooter/Tables/Character.json");
    // FString JsonString;
    // UE_LOG(LogTemp, Warning, TEXT("FilePath : %s"), *FilePath);

    // if(FFileHelper::LoadFileToString(JsonString, *FilePath))
    // {
        
    //     TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    //     TSharedPtr<FJsonObject> JsonObject;
    //     if (FJsonSerializer::Deserialize(Reader, JsonObject))
    //     {
    //         UE_LOG(LogTemp, Warning, TEXT("FilePath IsVaild!!!!!!!!!!!!!"));
    //     }
    // }
}
