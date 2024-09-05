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
	void Init();
private:
	static UCharacterManager* _Instance;
	// TSharedPtr<class FJsonObject> JsonObject;
};
