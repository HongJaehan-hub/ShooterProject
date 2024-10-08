// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameGameMode.generated.h"

UCLASS(minimalapi)
class AShooterGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterGameGameMode();
	virtual void StartPlay() override;

private:
	void CreateMainHUD();
	void ChangeToGameStartCamera();
	void CreateDefaultCharacter();
	void SetInputMode(bool bOnlyUIMode);
private:
	TWeakObjectPtr<class UMainHUDWidget> MainHUDWeakPtr;
};



