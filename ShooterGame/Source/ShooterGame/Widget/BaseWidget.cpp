// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"

void UBaseWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UBaseWidget::NativeDestruct()
{
    Super::NativeDestruct();
}

void UBaseWidget::SetVisible(bool bVisible)
{
    SetVisibility(bVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}
