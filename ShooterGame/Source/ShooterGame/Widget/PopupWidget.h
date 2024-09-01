// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "PopupWidget.generated.h"

// FPopupParam 구조체 정의
USTRUCT(BlueprintType)
struct FPopupParam
{
    GENERATED_BODY()

public:
    FPopupParam() {}
};

// 템플릿 인터페이스 정의
template<typename TParam>
class IPopupInterface
{
public:
    virtual void OnInit(TParam Param) = 0;
};

UCLASS()
class SHOOTERGAME_API UPopupWidget : public UBaseWidget, public IPopupInterface<FPopupParam>
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void Open();

	UFUNCTION(BlueprintCallable)
	virtual void OnInit(FPopupParam Param = FPopupParam());

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
