// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventParams.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UEventParamBase : public UObject
{
	GENERATED_BODY()
	
};

UCLASS()
class SHOOTERGAME_API UEventParamSkinChange : public UEventParamBase
{
	GENERATED_BODY()
public:
	UEventParamSkinChange(){};
public:
	int32 ChangeSkinIndex = 0;
};


