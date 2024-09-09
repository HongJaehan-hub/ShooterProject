// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterManager.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UCharacterManager : public UObject
{
	GENERATED_BODY()
	
public:
	static UCharacterManager* Instance();

	// Initialization of the character manager
	void Init(class UGameInstance* ShooterGameInstance);

	// Called By ShutDown
	void Destroyed();

	// Set Chracter By Character CMS Id
    void SetCharacter(int32 CharacterId);

	// Set Controller Possess To CurrentCharacter
	void PossessCurrentCharacter();

	int32 GetCurrentCharacterId();

	inline class APawn* GetCurrentPawn() { return CurrentPawn;};

private:
	class APawn* SpawnCharacter(int32 CharacterId);

	void HideAllCharacters();

	class APlayerStart* GetPlayerStart();
private:
	static UCharacterManager* _Instance;
	int32 CurrentCharacterId;

	UPROPERTY(VisibleAnywhere)
	TMap<int32, class APawn*> CachedPawn;
	
	UPROPERTY(VisibleAnywhere)
	class APawn* CurrentPawn;

	UPROPERTY(VisibleAnywhere)
	class UGameInstance* GameInstance;

	UPROPERTY()
	class APlayerStart* CachedPlayerStart;

	float CameraBlendTime = 3.f;
};
