// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CMSTable.generated.h"

UCLASS()
class SHOOTERGAME_API UCMSTable : public UObject
{
	GENERATED_BODY()
	
public:
	static UCMSTable* Instance();
	UCMSTable();
	void Init();

	TArray<TSharedPtr<FJsonValue>> GetTable(FString TableName);
	TSharedPtr<FJsonObject> GetTableRow(FString TableName, int32 CmsId);
private:
	static UCMSTable* _Instance;
	TMap<FString, TArray<TSharedPtr<FJsonValue>>> CachedTables;
	FString TablePath;
};
