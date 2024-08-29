// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "PopupWidget.generated.h"

UINTERFACE(Blueprintable)
class UPopupInterface : public UInterface
{
    GENERATED_BODY()
};

class IPopupInterface
{
    GENERATED_BODY()

public:
    template<typename T>
    void OnInit(T param);
};

UCLASS()
class SHOOTERGAME_API UPopupWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	class PopupParams{};

public:
	void Open();
	void Close();
	// virtual void OnInit(PopupParams Param);

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

// template<typename T>
// inline void UPopupWidget::OnInit(T Param)
// {

// }
