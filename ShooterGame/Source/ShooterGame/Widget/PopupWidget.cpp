// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupWidget.h"
#include "../UIManager.h"

void UPopupWidget::OnInit(FPopupParam Param)
{
    PlayOpenAnimation();
}

void UPopupWidget::Open()
{
    UE_LOG(LogTemp, Warning, TEXT("Open !!!!!!!!!!!!!!!!!!"));
    PlayOpenAnimation();
}

void UPopupWidget::Opening()
{
    
}

void UPopupWidget::Opened()
{

}

void UPopupWidget::Closing()
{

}

void UPopupWidget::Close()
{
    PlayCloseAnimation();
}

void UPopupWidget::Closed()
{
    UUIManager::Instance()->ClosePopup(this);
}