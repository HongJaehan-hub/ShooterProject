// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UObjPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjPool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	class AObjectPoolActor* GetObject();

    UFUNCTION(BlueprintCallable)
	void ReturnObject(class AObjectPoolActor* Object);

private:
	void ExpandPoolSize();
    void CreateAndAddToPool(int Size);
    class AObjectPoolActor *SpawnPoolActor();

public:
    UPROPERTY(EditAnywhere, Category="ObjectPool")
	TSubclassOf<class AObjectPoolActor> PooledObjectClass;

	UPROPERTY(EditAnywhere, Category="ObjectPool")
	int SizeOfPool = 1;

private:
	TArray<class AObjectPoolActor*> Pool;
	int ExpandSize = 1;
};
