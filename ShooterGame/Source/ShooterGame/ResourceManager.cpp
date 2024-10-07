// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceManager.h"

UResourceManager* UResourceManager::_Instance = nullptr;

UResourceManager *UResourceManager::Instance()
{
    if(_Instance == nullptr)
    {
        _Instance = NewObject<UResourceManager>();
        _Instance->AddToRoot(); // GC 방지
    }
    return _Instance;
}

UResourceManager::UResourceManager()
{
    CachedContentPath.Reset();
}

void UResourceManager::Init()
{
}

FString UResourceManager::GetAssetPath(const FString &AssetName)
{
    if(CachedContentPath.Contains(AssetName))
        return CachedContentPath[AssetName];
    
    FString FilePath = FPaths::ProjectContentDir() / TEXT("Shooter/Tables/ContentPath.json");
    FString JsonString;
    if(FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
        TSharedPtr<FJsonObject> JsonObject;

        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            FString AssetPath = JsonObject->GetStringField(AssetName);
            CachedContentPath.Add(AssetName, AssetPath);
            return AssetPath;
        }
    }
    return FString();
}

FString UResourceManager::GetAssetClassPath(const FString &ClassName)
{
    return GetAssetPath(ClassName) + TEXT("_C");
}
