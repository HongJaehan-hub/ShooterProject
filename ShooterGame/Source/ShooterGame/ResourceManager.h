// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ResourceManager.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UResourceManager : public UObject
{
	GENERATED_BODY()
	
public:
	UResourceManager();	
	static UResourceManager* Instance();
	
	void Init();
	FString GetAssetPath(const FString& AssetName);
	FString GetAssetClassPath(const FString& ClassName);
	class UUserWidget* CreateWidget(UObject* WorldContextObject, const FString& WidgetName);

private:
	static UResourceManager* _Instance;
	FString ContentTablePath;

	TMap<FString, FString> CachedContentPath;
};
