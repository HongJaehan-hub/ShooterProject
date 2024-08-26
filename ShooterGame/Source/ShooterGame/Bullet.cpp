// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	BulletMesh->SetupAttachment(Root);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectTileMovement"));
	ProjectileMovementComponent->InitialSpeed = 20000.f;
	ProjectileMovementComponent->bSimulationEnabled = false;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	BulletMesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBeginOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::ReturnToObjectPool()
{
	ProjectileMovementComponent->bSimulationEnabled = false;
	Super::ReturnToObjectPool();
}

void ABullet::Fire(FVector Direction)
{
	ProjectileMovementComponent->bSimulationEnabled = true;
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
	bProjectileActive = true;
}

void ABullet::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(bProjectileActive)
	{
		ReturnToObjectPool();
		bProjectileActive = false;
		if(ParticleSpark)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSpark, GetActorLocation());
		}
	}
}

void ABullet::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if(OtherActor != GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("On Hit!!!!!!!!!!!!!!"));
		ReturnToObjectPool();
	}	
}
