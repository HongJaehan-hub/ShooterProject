// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Templates/Function.h"
#include "Widget/PopupWidget.h"
#include "Widget/SkinChangePopupWidget.h"
#include "UIManager.generated.h"

UCLASS()
class SHOOTERGAME_API UUIManager : public UObject
{
	GENERATED_BODY()
	
public:
	static UUIManager* Instance();
	void Init();

	template<typename T, typename TParam>
	T *OpenPopup(UObject* WorldContextObject, const FString& WidgetName, TParam &PopupParam = FPopupParam());

	template<typename T>
	T *AddWidget(UObject *WorldContextObject, FString WidgetName);

	void ClosePopup(UUserWidget* UserWidget);
	bool IsAnyPopupOpened();
	bool IsWidgetOpened(FString WidgetName);
	void SetImage(class UImage* Image, FString &ImagePath);

private:
	UUIManager();
	~UUIManager();

private:
	static UUIManager* _Instance;
	TArray<UUserWidget*> WidgetStack;

private:
	UUserWidget* CreateWidget(UObject* WorldContextObject, const FString& WidgetName);
};

template <typename T, typename TParam>
inline T *UUIManager::OpenPopup(UObject *WorldContextObject, const FString &WidgetName, TParam &PopupParam)
{
	static_assert(TIsDerivedFrom<T, UPopupWidget>::Value, "must be derived from UPopupWidget");

	UUserWidget* Widget = CreateWidget(WorldContextObject, WidgetName);
    if(Widget)
    {
        Widget->AddToViewport();
        WidgetStack.Add(Widget);

		T* PopupWidget = Cast<T>(Widget);
		if(PopupWidget)
		{
			PopupWidget->OnInit(PopupParam);
			PopupWidget->Open();
		}
		return PopupWidget;
    }

    return nullptr;
}

template <typename T>
inline T *UUIManager::AddWidget(UObject *WorldContextObject, FString WidgetName)
{
	UUserWidget* Widget = CreateWidget(WorldContextObject, WidgetName);
	if(Widget == nullptr)
    	return nullptr;

	Widget->AddToViewport();
	WidgetStack.Add(Widget);
	return Cast<T>(Widget);
}
