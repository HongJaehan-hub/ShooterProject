// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameInstance.h"
#include "UIManager.h"
#include "ShooterEventManager.h"

void UShooterGameInstance::Init()
{
    Super::Init();
    UUIManager::Instance()->Init();
    UShooterEventManager::Instance()->Init();
}
