// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"
#include "Components/DynamicEntryBox.h"
#include "CharacterListEntry.h"
#include "../CMSTable.h"
#include "../CharacterManager.h"

void UMainHUDWidget::OnInit()
{
    // 캐릭터 선택 목록 초기화
    CreateCharacterListEntries();
}

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

void UMainHUDWidget::SelectCharacter(int32 CharacterId)
{
    UCharacterManager::Instance()->SetCharacter(CharacterId);
    for(auto &Entry : CharacterListEntries)
    {
        bool IsSelected = Entry->GetCharaterId() == CharacterId;
        Entry->SetSelect(IsSelected);
    }
}

void UMainHUDWidget::StartGame()
{
    UCharacterManager::Instance()->PossessCurrentCharacter();
}