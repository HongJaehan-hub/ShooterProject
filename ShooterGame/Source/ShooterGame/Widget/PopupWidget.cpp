// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupWidget.h"
#include "../UIManager.h"

// void UPopupWidget::OnInit(PopupParams Param)
// {

// }

void UPopupWidget::Opening()
{
    
}

void UPopupWidget::Opened()
{

}

void UPopupWidget::Closing()
{

}

void UPopupWidget::Open()
{
    PlayOpenAnimation();
}

void UPopupWidget::Close()
{

}

void UPopupWidget::Closed()
{
    UUIManager::Instance()->ClosePopup(this);
}