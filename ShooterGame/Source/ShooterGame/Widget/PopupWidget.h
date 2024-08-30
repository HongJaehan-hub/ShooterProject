// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "PopupWidget.generated.h"

USTRUCT(BlueprintType)
struct FPopupParam
{
    GENERATED_BODY()

public:
	FPopupParam(){};
};

UCLASS()
class SHOOTERGAME_API UPopupWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void Open(const FPopupParam& param = FPopupParam());

	UFUNCTION(BlueprintCallable)
	virtual void Close();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayOpenAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCloseAnimation();

protected:
	UFUNCTION(BlueprintCallable)
	virtual void Opening();

	UFUNCTION(BlueprintCallable)
	virtual void Opened();

	UFUNCTION(BlueprintCallable)
	virtual void Closing();

	UFUNCTION(BlueprintCallable)
	virtual void Closed();
};
