# 컨텐츠 경로 제작 툴
플러그인 생성하여 UEditorUtilityWidget상속, C++ 제작

<br>**코드**
<br>[ContentPathCreator.h](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Plugins/CppEditorWidget/Source/CppEditorWidget/Public/ContentPathCreator.h)
<br>[ContentPathCreator.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Plugins/CppEditorWidget/Source/CppEditorWidget/Private/ContentPathCreator.cpp)

## UEditorUtilityWidget 생성
![image](https://github.com/user-attachments/assets/554ea05c-2c49-4e86-a315-e2f3502e45f8)
![image](https://github.com/user-attachments/assets/c6eb49c6-cc28-4682-96e9-b52d3ddc681d)
<br> 생성 버튼 클릭 시 <br>해당 경로에 에셋들을 순회하여 에셋 이름을 Key, 에셋 경로를 Value로 하는 json 파일 생성

## ContentPathCreator.cpp
```
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
```

<br>실행 영상<br>
![2024-10-07142833-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/88534eb9-6499-4fa0-82ca-9153bd2be1ef)

# ResourceManager
리소스는 에셋 매니저를 통해서 생성/접근 가능하도록 구현

<br>**코드**
<br>[ResourceManager.h](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/ResourceManager.h)
<br>[ResourceManager.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/ResourceManager.cpp)

## ResourceManager.cpp
```
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
```



