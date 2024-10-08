// Fill out your copyright notice in the Description page of Project Settings.

#include "UIManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Widget/PopupWidget.h"
#include "ShooterPlayerController.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Styling/SlateBrush.h" 
#include "ResourceManager.h"

UUIManager* UUIManager::_Instance = nullptr;

UUIManager::UUIManager()
{
    WidgetStack.Reset();
}

UUIManager::~UUIManager()
{
    WidgetStack.Reset();
}


UUserWidget * UUIManager::CreateWidget(UObject * WorldContextObject, const FString & WidgetName)
{
    UResourceManager* ResourceManager = UResourceManager::Instance();
    if(!ResourceManager)
        return nullptr;

    return ResourceManager->CreateWidget(WorldContextObject, WidgetName);
}

UUIManager *UUIManager::Instance()
{
    if(_Instance == nullptr)
    {
        _Instance = NewObject<UUIManager>();
        _Instance->AddToRoot(); // GC 방지
    }
    return _Instance;
}

void UUIManager::Init()
{
    WidgetStack.Reset();
}

void UUIManager::ClosePopup(UUserWidget *UserWidget)
{
    int removedCnt = WidgetStack.Remove(UserWidget);
    UserWidget->RemoveFromParent();
    if(WidgetStack.Num() == 0)
    {
        UWorld* World = UserWidget->GetWorld();
        if(World)
        {
            AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(World->GetFirstPlayerController());
            if(PlayerController)
                PlayerController->SetUIMode(false);
        }
    }
}

bool UUIManager::IsAnyPopupOpened()
{
    return WidgetStack.Num() > 0;
}

bool UUIManager::IsWidgetOpened(FString WidgetName)
{
    if(WidgetStack.Num() == 0)
        return false;

    for(auto &Widget : WidgetStack)
    {
        if(Widget != nullptr && Widget->GetName() == WidgetName)
            return true;
    }
    return false;
}

void UUIManager::SetImage(UImage* Image, FString& ImagePath)
{
    if(Image == nullptr)
        return;
    
    UTexture2D* LoadedTexture = LoadObject<UTexture2D>(nullptr, *ImagePath);
    if(LoadedTexture)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(LoadedTexture);
        Image->SetBrush(Brush);
    }
}
