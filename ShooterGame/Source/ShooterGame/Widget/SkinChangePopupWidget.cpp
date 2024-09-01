// Fill out your copyright notice in the Description page of Project Settings.


#include "SkinChangePopupWidget.h"

void USkinChangePopupWidget::OnInit(FChangeSkinPopupParam Param)
{
    Super::OnInit(Param);
    SelectedSkinSlotIndex = Param.SelectSkinIndex;
    Refresh();
}

void USkinChangePopupWidget::Close()
{
    Super::Close();
}
