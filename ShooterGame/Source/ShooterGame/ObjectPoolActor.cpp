// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolActor.h"
#include "ObjPool.h"

// Sets default values
AObjectPoolActor::AObjectPoolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AObjectPoolActor::SetParentObjectPool(UObjPool* ObjectPool)
{ 
	ParentObjectPool = ObjectPool;
}

void AObjectPoolActor::SetActive(bool bActive)
{
	// 액터의 충돌 처리
    SetActorEnableCollision(bActive);
    
    // 액터 숨김 처리
    SetActorHiddenInGame(!bActive);

    // 액터의 틱 처리
    SetActorTickEnabled(bActive);
}

// Called when the game starts or when spawned
void AObjectPoolActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectPoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectPoolActor::ReturnToObjectPool()
{
	if(ParentObjectPool != nullptr)
	{
		ParentObjectPool->ReturnObject(this);
	}
}

