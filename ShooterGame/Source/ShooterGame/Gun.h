// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERGAME_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Fire();

	UFUNCTION()
	int GetBulletCount();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "Particels")
	UParticleSystem* FireFlash;
	
	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	class UObjPool* ObjectPool;
private:
	uint8 BulletCount = 100;
	float LastFiredTime = 0;
	float FireRate = 0.2f;
};
