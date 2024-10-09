// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

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
    
    // ContentPath.json 파일을 읽어서 Asset 경로를 가져옴
    FString FilePath = FPaths::ProjectContentDir() / TEXT("Shooter/Tables/ContentPath.json");
    FString JsonString;

    // 파일을 읽어서 JSON 객체로 변환
    if(FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
        TSharedPtr<FJsonObject> JsonObject;

        // JSON 객체로 변환 성공하면 Asset 경로를 가져옴
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

UUserWidget *UResourceManager::CreateWidget(UObject *WorldContextObject, const FString &WidgetName)
{
    //  Widget 클래스 경로 가져오기
    FString AssetClassPath = GetAssetClassPath(WidgetName);
    UClass* WidgetClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, *AssetClassPath);

    if(WidgetClass != nullptr)
    {
        // Widget 생성
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
        return UWidgetBlueprintLibrary::Create(WorldContextObject, WidgetClass, PlayerController);
    }
    return nullptr;
}
