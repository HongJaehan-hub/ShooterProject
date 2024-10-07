// Fill out your copyright notice in the Description page of Project Settings.


#include "CMSTable.h"

UCMSTable::UCMSTable()
{
    // 기본 경로 초기화
    TablePath = FPaths::ProjectContentDir() / TEXT("Shooter/Tables");
}

UCMSTable* UCMSTable::_Instance = nullptr;
UCMSTable *UCMSTable::Instance()
{
    if(_Instance == nullptr)
    {
        _Instance = NewObject<UCMSTable>();
        _Instance->AddToRoot(); // GC 방지
    }
    return _Instance;
}

void UCMSTable::Init()
{
    CachedTables.Reset();
}

TArray<TSharedPtr<FJsonValue>> UCMSTable::GetTable(FString TableName)
{
    if(CachedTables.Contains(TableName))
        return CachedTables[TableName];
    
    FString JsonString;
    FString FilePath = FString::Printf(TEXT("%s/%s.json"), *TablePath, *TableName);
    if(FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
        TArray<TSharedPtr<FJsonValue>> JsonArray;

        if (FJsonSerializer::Deserialize(Reader, JsonArray) && JsonArray.Num() > 0)
        {
            CachedTables.Add(TableName, JsonArray);
            return JsonArray;
        }
    }
    return TArray<TSharedPtr<FJsonValue>>();
}

TSharedPtr<FJsonObject> UCMSTable::GetTableRow(FString TableName, int32 CmsId)
{
    auto Table = GetTable(TableName);
    for(const TSharedPtr<FJsonValue>& JsonValue : Table)
    {
        TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();
        if(JsonObject.IsValid())
        {
            if(JsonObject->GetNumberField(TEXT("Id")) == CmsId)
            {
                return JsonObject;
            }
        }
    }
    return nullptr;
}
