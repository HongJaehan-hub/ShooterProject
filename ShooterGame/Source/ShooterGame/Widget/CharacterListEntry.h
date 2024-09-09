// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "CharacterListEntry.generated.h"

DECLARE_DELEGATE_OneParam(FOnEntryClicked, int32);

USTRUCT(BlueprintType)
struct FCharacterListEntryParam
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	int32 CharacterId;

	UPROPERTY()
	FString CharacterName;

	UPROPERTY()
	FString ThumbnailImg;
};

UCLASS()
class SHOOTERGAME_API UCharacterListEntry : public UBaseWidget
{
	GENERATED_BODY()

public:
	void InitCharacterEntry(const FCharacterListEntryParam& Param, FOnEntryClicked InCallback);

	UFUNCTION()
	void SetSelect(bool IsSelected);

	UFUNCTION()
	inline int32 GetCharaterId() {return CharacterId; };

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
public:
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonEntry;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImageCharacter;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImageCheck;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextName;

private:
	UFUNCTION()
	void OnClicked();
private:
	FOnEntryClicked ButtonClickedCallback;
	int32 CharacterId;
};
