// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"

void UBaseWidget::SetVisible(bool bVisible)
{
    SetVisibility(bVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}
