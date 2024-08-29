// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjPool.h"
#include "ObjectPoolActor.h"

// Sets default values for this component's properties
UObjPool::UObjPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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

	ULevel* Level = World->GetCurrentLevel();
	for(uint8 i = 0; i < Size; ++i)
	{
		AObjectPoolActor* PooledObject = SpawnPoolActor();
		PooledObject->SetActive(false);
		Pool.Push(PooledObject);
	}
}

AObjectPoolActor* UObjPool::SpawnPoolActor()
{
	// Spawn 후 비활성화 상태로 설정
	AObjectPoolActor* PooledObject = GetWorld()->SpawnActor<AObjectPoolActor>(PooledObjectClass);
	PooledObject->SetActorHiddenInGame(true);
	PooledObject->SetParentObjectPool(this);
	return PooledObject;
}

AObjectPoolActor *UObjPool::GetObject()
{
	// 현재 풀에 남아있는 사용할 수 있는 Actor가 없는 경우 추가
	if(Pool.Num() <= 0)
		ExpandPoolSize();
	
	// 미리 생성된 객체를 풀에서 꺼내와서 사용
	AObjectPoolActor* PooledObject = Pool.Pop();
	if(PooledObject == nullptr) 
		return nullptr;

	PooledObject->SetActive(true);
    return PooledObject;
}

void UObjPool::ReturnObject(AObjectPoolActor *Object)
{
	// 사용 완료된 객체 풀로 돌려줌
	Object->SetActive(false);
	Pool.Push(Object);
}

void UObjPool::ExpandPoolSize()
{
	CreateAndAddToPool(ExpandSize);
}
