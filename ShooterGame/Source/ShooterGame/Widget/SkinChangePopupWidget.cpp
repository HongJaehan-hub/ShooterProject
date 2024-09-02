// Fill out your copyright notice in the Description page of Project Settings.


#include "SkinChangePopupWidget.h"
#include "../ShooterEventManager.h"

void USkinChangePopupWidget::OnInit(FChangeSkinPopupParam Param)
{
    Super::OnInit(Param);
    SelectedSkinSlotIndex = Param.SelectSkinIndex;
    Refresh();
}

void USkinChangePopupWidget::Close()
{
    Super::Close();
    UEventParamSkinChange* EventParam = NewObject<UEventParamSkinChange>();
    if(EventParam)
    {
        EventParam->ChangeSkinIndex = SelectedSkinSlotIndex;
        UShooterEventManager::Instance()->BroadcastEvent(EEventType::Event_ChangeSkin, EventParam);
    }
}
