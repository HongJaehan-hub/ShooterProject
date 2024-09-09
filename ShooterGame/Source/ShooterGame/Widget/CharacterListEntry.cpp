// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterListEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../CharacterManager.h"
#include "Components/Image.h"
#include "../UIManager.h"

void UCharacterListEntry::NativeConstruct()
{
    Super::NativeConstruct();
    if(ButtonEntry)
    {
        ButtonEntry->OnClicked.AddDynamic(this, &UCharacterListEntry::OnClicked);
    }
}

void UCharacterListEntry::NativeDestruct()
{
    Super::NativeDestruct();

    // ButtonClickedCallback.Unbind();
    // ButtonEntry->OnClicked.Remove();
}

void UCharacterListEntry::InitCharacterEntry(const FCharacterListEntryParam &Param, FOnEntryClicked InCallback)
{
    ButtonClickedCallback = InCallback;
    CharacterId = Param.CharacterId;
    int32 CurrentCharacterId = UCharacterManager::Instance()->GetCurrentCharacterId();
    ImageCheck->SetVisibility(CharacterId == CurrentCharacterId ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);  
    TextName->SetText(FText::FromString(Param.CharacterName));

    FString ImagePath = FString::Format(TEXT("/Game/Shooter/WidgetBlueprints/Images/{0}.{1}"), {Param.ThumbnailImg, Param.ThumbnailImg});
    UUIManager::Instance()->SetImage(ImageCharacter, ImagePath);
}

void UCharacterListEntry::SetSelect(bool IsSelected)
{
    ImageCheck->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);  
}

void UCharacterListEntry::OnClicked()
{
    if(ButtonClickedCallback.IsBound())
    {
        ButtonClickedCallback.Execute(CharacterId);
    }
}