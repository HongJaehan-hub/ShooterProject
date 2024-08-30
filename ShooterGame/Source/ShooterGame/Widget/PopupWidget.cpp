// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupWidget.h"
#include "../UIManager.h"

void UPopupWidget::Opening()
{
    
}

void UPopupWidget::Opened()
{

}

void UPopupWidget::Closing()
{

}

void UPopupWidget::Open(const FPopupParam& param)
{
    PlayOpenAnimation();
}

void UPopupWidget::Close()
{
    PlayCloseAnimation();
}

void UPopupWidget::Closed()
{
    UUIManager::Instance()->ClosePopup(this);
}