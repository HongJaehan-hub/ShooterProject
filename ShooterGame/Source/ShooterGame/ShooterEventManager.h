// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventParams.h"
#include "ShooterEventManager.generated.h"

UENUM(BlueprintType)
enum class EEventType : uint8
{
    Event_ChangeSkin,
};

UINTERFACE()
class SHOOTERGAME_API UEventListener : public UInterface
{
	GENERATED_BODY()
};

class SHOOTERGAME_API IEventListener
{
	GENERATED_BODY()
public:
	virtual void OnReceived(EEventType EventType, UEventParamBase* EventParam) = 0;
};

UCLASS()
class SHOOTERGAME_API UShooterEventManager : public UObject
{
	GENERATED_BODY()
	
public:
	static UShooterEventManager* Instance();
	void Init();

public:
	void AddListener(EEventType EventType, IEventListener* Listener);
	void RemoveListener(EEventType EventType, IEventListener* Listener);
	void BroadcastEvent(EEventType EventType, UEventParamBase* Param = nullptr);
	void RemoveAllListener();
private:
	static UShooterEventManager* _Instance;
	TMap<EEventType, TArray<IEventListener*>> Listeners;
};
