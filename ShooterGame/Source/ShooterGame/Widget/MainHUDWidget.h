// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UMainHUDWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UDynamicEntryBox* DynamicEntryBoxCharacterList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* PageWidgetSwitcher;

public:
	void OnInit();
};
