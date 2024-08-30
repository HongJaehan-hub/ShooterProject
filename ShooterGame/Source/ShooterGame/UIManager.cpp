// Fill out your copyright notice in the Description page of Project Settings.

#include "UIManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Widget/PopupWidget.h"
#include "ShooterPlayerController.h"

UUIManager* UUIManager::_Instance = nullptr;

UUIManager::UUIManager()
{
    
}

UUIManager::~UUIManager()
{

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

UUserWidget *UUIManager::CreateWidget(UObject *WorldContextObject, const FString &WidgetName)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
    FString Path = "WidgetBlueprint'/Game/Shooter/WidgetBlueprints/" +  WidgetName + "." + WidgetName + "_C'";
    UClass* WidgetClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, *Path);

    if(WidgetClass != nullptr)
    {
        return UWidgetBlueprintLibrary::Create(WorldContextObject, WidgetClass, PlayerController);
    }
    return nullptr;
}

void UUIManager::ClosePopup(UUserWidget *UserWidget)
{
    WidgetStack.Remove(UserWidget);
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

    for(auto Widget : WidgetStack)
    {
        if(Widget != nullptr && Widget->GetName() == WidgetName)
            return true;
    }
    return false;
}
