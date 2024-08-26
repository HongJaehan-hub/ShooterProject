[ObjectPool.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/ObjPool.cpp)

```
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UObjPool : public UActorComponent
```
<br>ActorComponent로 제작하여 원하는 Actor에 추가하여 사용 (클래스 이름은 엔진의 ObjectPool과 겹쳐 ObjPool로 설정)

```
public:
  UPROPERTY(EditAnywhere, Category="ObjectPool")
  TSubclassOf<class AObjectPoolActor> PooledObjectClass;
```
<br>사용 할 Actor를 BP에서 지정 가능하도록 PooledObjectClass 변수 추가

<br>**cpp 구현부**
```
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
```
<br> 총알처럼 빈번하고 많은 객체가 사용되는 Actor는 최적화가 필요
<br> Pool에 미리 생성된 Actor를 사용하고 반납하는 구조를 사용해 관리

<br>**실제 Gun 하위에서 ObjectPoolComponent를 사용하여 Bullet을 사용하는 코드**
```
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
		Bullet->SetActorLocationAndRotation(StartPos, GetOwner()->GetActorRotation());
		Bullet->Fire(GetOwner()->GetActorRotation().Vector());
	}
}
```
