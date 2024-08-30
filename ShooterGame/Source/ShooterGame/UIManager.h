// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Templates/Function.h"
#include "Widget/PopupWidget.h"
#include "UIManager.generated.h"

UCLASS()
class SHOOTERGAME_API UUIManager : public UObject
{
	GENERATED_BODY()
	
public:
	static UUIManager* Instance();

	template<typename T>
	T *OpenPopup(UObject* WorldContextObject, const FString& WidgetName, FPopupParam PopupParam = FPopupParam());

	void ClosePopup(UUserWidget* UserWidget);
	bool IsAnyPopupOpened();
	bool IsWidgetOpened(FString WidgetName);
private:
	UUserWidget* CreateWidget(UObject* WorldContextObject, const FString& WidgetName);

private:
	UUIManager();
	~UUIManager();

	static UUIManager* _Instance;
	TArray<UUserWidget*> WidgetStack;
};

template <typename T>
inline T *UUIManager::OpenPopup(UObject *WorldContextObject, const FString &WidgetName, FPopupParam PopupParam)
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
			PopupWidget->Open(PopupParam);
		}
		return PopupWidget;
    }

    return nullptr;
}
