// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopupWidget.h"
#include "SkinChangePopupWidget.generated.h"

USTRUCT(BlueprintType)
struct FChangeSkinPopupParam : public FPopupParam
{
    GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 SelectSkinIndex = 0;

	FChangeSkinPopupParam(){};
	FChangeSkinPopupParam(int32 SelectIndex) : SelectSkinIndex(SelectIndex) {};
};

UCLASS()
class SHOOTERGAME_API USkinChangePopupWidget : public UPopupWidget, public IPopupInterface<FChangeSkinPopupParam>
{
	GENERATED_BODY()

public:
	virtual void OnInit(FChangeSkinPopupParam Param = FChangeSkinPopupParam());
	virtual void Close() override;

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SelectedSkinSlotIndex;
};
