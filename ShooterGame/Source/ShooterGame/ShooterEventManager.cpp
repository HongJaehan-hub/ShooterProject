// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEventManager.h"

UShooterEventManager* UShooterEventManager::_Instance = nullptr;

UShooterEventManager *UShooterEventManager::Instance()
{
    if(_Instance == nullptr)
    {
        _Instance = NewObject<UShooterEventManager>();
        _Instance->AddToRoot(); // GC 방지
    }
    return _Instance;
}

void UShooterEventManager::Init()
{
    
}
