# 캐릭터 선택 기능
<br> 1. MainHUD에 캐릭터 선택 메뉴창을 만들고 진입

<br> 2. WidgetSwitcher 캐릭터 선택 페이지로 전환

<br> 3. Character.json파일을 CMSTable 통해 테이블 전체를 가져옴

<br> 4. DynamicEntryBox로 선택 Entry Widget을 동적 생성

<br> 5. Entry 선택 시 Character Asset 정보로 캐릭터 Spawn

<br> 6. 게임 시작 버튼 클릭 시 선택된 캐릭터 기준으로 Controller에 부착

## 코드
<br> [CharacterManager.h](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/CharacterManager.h)
<br> [CharacterManager.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/CharacterManager.cpp)
<br> [MainHUDWidget.h](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/Widget/MainHUDWidget.h)
<br> [MainHUDWidget.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/Widget/MainHUDWidget.cpp)

## Widget (WBP_MainHUD)
![image](https://github.com/user-attachments/assets/882f086a-0cee-421d-996e-ce00a928c04a)
![image](https://github.com/user-attachments/assets/e2fd7454-eb24-4571-a2aa-dda8e3a6daaf)
<br> Entry 동적 생성을 위해 DynamicEntryBox 사용<br>

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
<br>**캐릭터 리스트 생성**<br>
![image](https://github.com/user-attachments/assets/dd7d9ca5-868d-4d63-8bf6-72e53b0ca6d7)
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

<br>**리스트 선택 시 캐릭터 변경**<br>
![2024-09-09181623-ezgif com-video-to-gif-converter (1)](https://github.com/user-attachments/assets/6fb2976d-8a9e-4017-a478-90f54ac1e4ab)


```
void UMainHUDWidget::SelectCharacter(int32 CharacterId)
{
    UCharacterManager::Instance()->SetCharacter(CharacterId);
    for(auto &Entry : CharacterListEntries)
    {
        bool IsSelected = Entry->GetCharaterId() == CharacterId;
        Entry->SetSelect(IsSelected);
    }
}
```
```
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
```

```
APawn* UCharacterManager::SpawnCharacter(int32 CharacterId)
{
    // Character Table에서 Asset 정보를 가져와 Spawn
    TSharedPtr<FJsonObject> CharacterCms = UCMSTable::Instance()->GetTableRow("Character", CharacterId);
    if(CharacterCms.IsValid())
    {  
        FString AssetName = CharacterCms->GetStringField(TEXT("CharacterAsset"));
        FString Path = CharacterAssetPath + AssetName + "." + AssetName + "_C";
        FSoftObjectPath SoftObjectPath(Path);
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
```

## 선택된 캐릭터로 게임 실행
https://github.com/user-attachments/assets/d6b1df9a-1ee9-438d-a2f0-6d155c874fa9


```
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
```
