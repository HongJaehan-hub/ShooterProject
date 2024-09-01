// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ShooterEventManager.generated.h"

UENUM(BlueprintType)
enum class EEventType : uint8
{
    Event_ChangeSkin,
};

// UINTERFACE()
// class SHOOTERGAME_API UEventListener : public UInterface
// {
// 	GENERATED_BODY()
// };

// class SHOOTERGAME_API IEventListener
// {
// 	GENERATED_BODY()
// public:
// 	virtual void OnReceived() = 0;
// };

template<typename T>
class IEventListener
{
	public:
	virtual void OnReceivedEvent(T Param) = 0;
}
// // 템플릿 인터페이스 정의
// template<typename TParam>
// class IEventListener
// {
// public:
//     virtual void OnInit(TParam Param) = 0;
// };

UCLASS()
class SHOOTERGAME_API UShooterEventManager : public UObject
{
	GENERATED_BODY()
	
public:
	static UShooterEventManager* Instance();
	void Init();

private:
	static UShooterEventManager* _Instance;
};
