# CMS Manager (테이블 관리 매니저)
엑셀 테이블로 만든 Json파일을 가져와서
필요한 테이블 정보를 가져올 수 있도록 CMSTable 클래스를 제작했습니다.

<br>**코드**
<br>[CMSTable.h](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/CMSTable.h)
<br>[CMSTable.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/CMSTable.cpp)

## CMSTable.h
```
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CMSTable.generated.h"

UCLASS()
class SHOOTERGAME_API UCMSTable : public UObject
{
	GENERATED_BODY()
	
public:
	static UCMSTable* Instance();
	UCMSTable();
	void Init();

	TArray<TSharedPtr<FJsonValue>> GetTable(FString TableName);
	TSharedPtr<FJsonObject> GetTableRow(FString TableName, int32 CmsId);
private:
	static UCMSTable* _Instance;
	TMap<FString, TArray<TSharedPtr<FJsonValue>>> CachedTables;
	FString TablePath;
};

```
**테이블 데이터 전체를 가져오거나 Id를 통해 일치하는 Row 정보만 가져오도록 구현**
<br>**TMap에 Table 이름으로 테이블 정보를 캐싱**

## CMSTable.cpp
```
#include "CMSTable.h"

UCMSTable::UCMSTable()
{
    // 기본 경로 초기화
    TablePath =  FPaths::ProjectContentDir() / TEXT("Shooter/Tables");
}

UCMSTable* UCMSTable::_Instance = nullptr;
UCMSTable *UCMSTable::Instance()
{
    if(_Instance == nullptr)
    {
        _Instance = NewObject<UCMSTable>();
        _Instance->AddToRoot(); // GC 방지
    }
    return _Instance;
}

void UCMSTable::Init()
{
    CachedTables.Reset();
}

TArray<TSharedPtr<FJsonValue>> UCMSTable::GetTable(FString TableName)
{
    if(CachedTables.Contains(TableName))
        return CachedTables[TableName];
    
    FString JsonString;
    FString FilePath = FString::Printf(TEXT("%s/%s.json"), *TablePath, *TableName);
    if(FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
        TArray<TSharedPtr<FJsonValue>> JsonArray;

        if (FJsonSerializer::Deserialize(Reader, JsonArray) && JsonArray.Num() > 0)
        {
            CachedTables.Add(TableName, JsonArray);
            return JsonArray;
        }
    }
    return TArray<TSharedPtr<FJsonValue>>();
}

TSharedPtr<FJsonObject> UCMSTable::GetTableRow(FString TableName, int32 CmsId)
{
    auto Table = GetTable(TableName);
    for(const TSharedPtr<FJsonValue>& JsonValue : Table)
    {
        TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();
        if(JsonObject.IsValid())
        {
            if(JsonObject->GetNumberField(TEXT("Id")) == CmsId)
            {
                return JsonObject;
            }
        }
    }
    return nullptr;
}
```

<br>json 파일들이 있는 Table 경로를 초기화해서 해당 경로에서 파일을 찾도록 함.
```
  TablePath =  FPaths::ProjectContentDir() / TEXT("Shooter/Tables");
```

<br>JsonReader로 json 파일을 가져오고, Deserialize를 통해 Json파일을 JsonArray형식으로 받아와 사용 가능한 데이터가 됨
```
  FString JsonString;
  FString FilePath = FString::Printf(TEXT("%s/%s.json"), *TablePath, *TableName);
  if(FFileHelper::LoadFileToString(JsonString, *FilePath))
  {
      TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
      TArray<TSharedPtr<FJsonValue>> JsonArray;

      if (FJsonSerializer::Deserialize(Reader, JsonArray) && JsonArray.Num() > 0)
      {
          CachedTables.Add(TableName, JsonArray);
          return JsonArray;
      }
  }
```

<br>JsonObject에서 GetNumberField를 사용해 Key값을 찾아서 Id와 일치하는 Json 정보를 반환시켜줌
```
TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();
if(JsonObject.IsValid())
{
  if(JsonObject->GetNumberField(TEXT("Id")) == CmsId)
  {
    return JsonObject;
  }
}
```

<br>

## Character json 정보를 가져와 이름과 이미지를 세팅<br>
![image](https://github.com/user-attachments/assets/28912edd-4710-49fa-b1fc-58f927fba53f)
![image](https://github.com/user-attachments/assets/656026be-4b02-4cd0-b3af-1f739cff4117)

## Character.json
```
[
  {
    "Id": 1000,
    "Name": "Wraith",
    "CharacterAsset":"BP_Character_Wraith", 
    "Image_Thumbnail": "Img_Thumbnail_Wraith"
  },
  {
    "Id": 1001,
    "Name": "Revenant",
    "CharacterAsset":"BP_Character_Revenant", 
    "Image_Thumbnail": "Img_Thumbnail_Revenant"

  },
  {
    "Id": 1002,
    "Name": "Murdock",
    "CharacterAsset":"BP_Character_Murdock", 
    "Image_Thumbnail": "Img_Thumbnail_Murdock"
  }
]
```

## 코드
```
void UMainHUDWidget::CreateCharacterListEntries()
{
    DynamicEntryBoxCharacterList->Reset();
    CharacterListEntries.Reset();

    int32 CurrentCharacterId = UCharacterManager::Instance()->GetCurrentCharacterId();
    auto CharacterJsonValues = UCMSTable::Instance()->GetTable("Character");
    if(CharacterJsonValues.Num() > 0)
    {
        for(const TSharedPtr<FJsonValue>& JsonValue : CharacterJsonValues)
        {
            TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();
            if(JsonObject.IsValid())
            {
                FString Name = JsonObject->GetStringField(TEXT("Name"));
                UCharacterListEntry* Entry = DynamicEntryBoxCharacterList->CreateEntry<UCharacterListEntry>();
                if(Entry)
                {
                    FCharacterListEntryParam Param;
                    Param.CharacterId = JsonObject->GetNumberField(TEXT("Id"));
                    Param.CharacterName = JsonObject->GetStringField(TEXT("Name"));
                    Param.ThumbnailImg = JsonObject->GetStringField(TEXT("Image_Thumbnail"));
                    Entry->InitCharacterEntry(Param, FOnEntryClicked::CreateUObject(this, &UMainHUDWidget::SelectCharacter));
                    Entry->SetSelect(CurrentCharacterId == Param.CharacterId);
                    CharacterListEntries.Add(Entry);
                }
            }
        }
    }
}
```
