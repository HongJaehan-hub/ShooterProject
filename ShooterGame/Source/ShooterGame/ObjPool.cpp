// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjPool.h"
#include "ObjectPoolActor.h"

// Sets default values for this component's properties
UObjPool::UObjPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UObjPool::BeginPlay()
{
	Super::BeginPlay();

	if(PooledObjectClass != nullptr)
	{
		CreateAndAddToPool(SizeOfPool);
	}
}

// Called every frame
void UObjPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjPool::CreateAndAddToPool(int Size)
{
	UWorld* World = GetWorld();
	if(PooledObjectClass == nullptr || World == nullptr)
		return;

	for(uint8 i = 0; i < Size; ++i)
	{
		AObjectPoolActor* PooledObject = SpawnPoolActor();
		PooledObject->SetActive(false);
		Pool.Push(PooledObject);
	}
}

AObjectPoolActor* UObjPool::SpawnPoolActor()
{
	AObjectPoolActor* PooledObject = GetWorld()->SpawnActor<AObjectPoolActor>(PooledObjectClass);
	PooledObject->SetActorHiddenInGame(true);
	PooledObject->SetParentObjectPool(this);
	return PooledObject;
}

AObjectPoolActor *UObjPool::GetObject()
{
	if(Pool.Num() <= 0)
		ExpandPoolSize();
	
	AObjectPoolActor* PooledObject = Pool.Pop();
	if(PooledObject == nullptr) 
		return nullptr;

	PooledObject->SetActive(true);
    return PooledObject;
}

void UObjPool::ReturnObject(AObjectPoolActor *Object)
{
	Object->SetActive(false);
	Pool.Push(Object);
}

void UObjPool::ExpandPoolSize()
{
	CreateAndAddToPool(ExpandSize);
}