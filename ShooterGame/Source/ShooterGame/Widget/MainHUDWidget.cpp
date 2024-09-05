// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"
#include "Components/DynamicEntryBox.h"

void UMainHUDWidget::OnInit()
{
    DynamicEntryBoxCharacterList->Reset();

    for(int i = 0; i < 10; ++i)
    {
        DynamicEntryBoxCharacterList->CreateEntry();
    }
}
