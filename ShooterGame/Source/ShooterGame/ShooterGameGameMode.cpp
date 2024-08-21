// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGameGameMode.h"
#include "ShooterGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShooterGameGameMode::AShooterGameGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Shooter/Blueprint/BP_PlayerCharacter"));
	{
		UE_LOG(LogTemp, Display, TEXT("[jh] Your message 2222"));
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
