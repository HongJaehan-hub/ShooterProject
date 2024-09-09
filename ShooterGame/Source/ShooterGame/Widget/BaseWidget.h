// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Refresh();

	UFUNCTION()
	void SetVisible(bool bVisible);
};
