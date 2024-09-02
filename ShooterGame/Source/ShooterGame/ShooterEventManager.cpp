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
    RemoveAllListener();
}

void UShooterEventManager::AddListener(EEventType EventType, IEventListener *Listener)
{
    TArray<IEventListener*>* ListenerArray = Listeners.Find(EventType);
    if(ListenerArray)
    {
        ListenerArray->Add(Listener);
    }
    else
    {
        Listeners.Add(EventType, TArray<IEventListener*>{Listener});
    }
}

void UShooterEventManager::RemoveListener(EEventType EventType, IEventListener * Listener)
{
    Listeners[EventType].Remove(Listener);
}

void UShooterEventManager::BroadcastEvent(EEventType EventType, UEventParamBase *Param)
{
    TArray<IEventListener*>* ListenerArray = Listeners.Find(EventType);
    if(ListenerArray)
    {
        for(auto* listener : *ListenerArray)
        {
            if(listener)
                listener->OnReceived(EventType, Param);
        }   
    }  
}

void UShooterEventManager::RemoveAllListener()
{
    Listeners.Reset();
}
