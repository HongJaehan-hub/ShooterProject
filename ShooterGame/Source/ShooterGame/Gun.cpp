// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ObjPool.h"
#include "Bullet.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunMesh->SetupAttachment(Root);

	ObjectPool = CreateDefaultSubobject<UObjPool>(TEXT("ObjectPool"));

	LastFiredTime = 0.f;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Fire()
{
	if(BulletCount <= 0)
		return;

	// check fire rate
	float CurrentTime = GetWorld()->GetTimeSeconds(); 
	if(CurrentTime - LastFiredTime < FireInterval)
		return;

	LastFiredTime = CurrentTime;
	UGameplayStatics::SpawnEmitterAttached(FireFlash, GunMesh, TEXT("MuzzleFlashSocket"));

	// OjbectPool에서 미사용중인 객체를 받아와 사용
	ABullet* Bullet = Cast<ABullet>(ObjectPool->GetObject());
	if(Bullet)
	{
		FVector StartPos = GunMesh->GetSocketLocation("MuzzleFlashSocket");
		Bullet->SetActorLocationAndRotation(StartPos, GunMesh->GetSocketRotation("MuzzleFlashSocket"));
		Bullet->Fire(Cast<APawn>(GetOwner())->GetControlRotation().Vector());
	}
}

int AGun::GetBulletCount()
{
	return BulletCount;
}
