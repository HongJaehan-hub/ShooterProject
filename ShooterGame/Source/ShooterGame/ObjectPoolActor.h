// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolActor.generated.h"

UCLASS()
class SHOOTERGAME_API AObjectPoolActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectPoolActor();

	void SetParentObjectPool(class UObjPool* ObjectPool);
	void SetActive(bool bActive);

	// Return Completed Obejct To Parent pool
    virtual void ReturnToObjectPool();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class UObjPool* ParentObjectPool;
};
