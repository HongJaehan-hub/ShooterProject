// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/ContentPathCreator.h"
#include "Components/Button.h"
#include "ContentPathCreator.h"
#include "AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Components/EditableTextBox.h"

UContentPathCreator::UContentPathCreator()
{
}

void UContentPathCreator::NativeConstruct()
{
    CreateButton->OnClicked.AddDynamic(this, &UContentPathCreator::OnCreateButtonClicked);
}

void UContentPathCreator::OnCreateButtonClicked()
{
    CreateUserWidgetContentPath();
}

void UContentPathCreator::CreateUserWidgetContentPath()
{
    // 에셋 레지스트리 모듈을 가져옴
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

    // Shooter 폴더 내의 모든 에셋을 가져옴
    TArray<FAssetData> AssetDataList;
    AssetRegistry.GetAssetsByPath(TEXT("/Game/Shooter"), AssetDataList, true);

    // JSON 객체 생성
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

    // 에셋 이름과 경로를 JSON 객체에 추가
    for(const FAssetData& AssetData : AssetDataList)
    {
        if(AssetData.IsValid())
        {
            FString AssetName = AssetData.AssetName.ToString();
            FString AssetPath = AssetData.GetSoftObjectPath().ToString();
            JsonObject->SetStringField(AssetName, AssetPath);
        }
    }

    // JSON 문자열로 변환
    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

    // 문자열로 저장한 JSON 파일을 저장
    FString JsonFilePath = FPaths::ProjectContentDir() / FilePathTextBox->GetText().ToString();
    FFileHelper::SaveStringToFile(OutputString, *JsonFilePath);

    UE_LOG(LogTemp, Display, TEXT("Create Content Path JSON File! : %s"), *JsonFilePath);
}
