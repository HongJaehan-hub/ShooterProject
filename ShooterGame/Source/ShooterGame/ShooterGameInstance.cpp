// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameInstance.h"
#include "UIManager.h"
#include "ShooterEventManager.h"
#include "CharacterManager.h"
#include "CMSTable.h"

void UShooterGameInstance::Init()
{
    Super::Init();
    UUIManager::Instance()->Init();
    UShooterEventManager::Instance()->Init();
    UCharacterManager::Instance()->Init(); 
    UCMSTable::Instance()->Init();
}
