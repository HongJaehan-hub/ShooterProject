# EventManager
디커플링을 위해 EventManager을 제작해봤습니다.
<br> 이벤트 타입을 만들어 Listener에 등록 후 Event 발생 시 반응할 수 있도록 구현했습니다.
<br> 스킨 변경 팝업이 닫히면 선택된 Index 기준으로 Event를 발생시켜 Character의 Mesh를 변경할 수 있도록 하였습니다.
<br> 팝업과 캐릭터는 서로 참조를 하지않고 디커플링 되어있는 상태로 진행이 가능합니다.

**코드**
<br>[ShooterEventManager.h](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/ShooterEventManager.h)
<br>[ShooterEventManager.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/ShooterEventManager.cpp)

## EventManager.h
```
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventParams.h"
#include "ShooterEventManager.generated.h"

UENUM(BlueprintType)
enum class EEventType : uint8
{
    Event_ChangeSkin,
};

UCLASS()
class SHOOTERGAME_API UShooterEventManager : public UObject
{
	GENERATED_BODY()
	
public:
	static UShooterEventManager* Instance();
	void Init();

public:
	void AddListener(EEventType EventType, IEventListener* Listener);
	void RemoveListener(EEventType EventType, IEventListener* Listener);
	void BroadcastEvent(EEventType EventType, UEventParamBase* Param = nullptr);
	void RemoveAllListener();
private:
	static UShooterEventManager* _Instance;
	TMap<EEventType, TArray<IEventListener*>> Listeners;
};

```
**singleton으로 접근가능 하도록 instance 구현**
<br>**TMap<EEventType, TArray<IEventListener>> Listeners;**
<br>**Listener을 EventType에 따라 저장할 수 있도록 TMap과 TArray를 사용해서 구현**<br>

## EventListener Interface
```
UINTERFACE()
class SHOOTERGAME_API UEventListener : public UInterface
{
	GENERATED_BODY()
};

class SHOOTERGAME_API IEventListener
{
	GENERATED_BODY()
public:
	virtual void OnReceived(EEventType EventType, UEventParamBase* EventParam) = 0;
};
```
**Event를 등록하고 받아오기 위해 Interface를 제작**

## Event 적용 (캐릭터 스킨 변경)
```
UENUM(BlueprintType)
enum class EEventType : uint8
{
    Event_ChangeSkin,
};
```
**플레이어의 Mesh Skin을 변경해줄 EventType Enum생성**
<br>

```
// IEventListner상속
class AShooterGameCharacter : public ACharacter, public IEventListener

////// ShooterGameCharacter.cpp
// Listener 등록
void AShooterGameCharacter::AddToEventListener()
{
	UShooterEventManager::Instance()->AddListener(EEventType::Event_ChangeSkin, this);
}

// 이벤트 Receive
void AShooterGameCharacter::OnReceived(EEventType EventType, UEventParamBase *EventParam)
{
	UEventParamSkinChange* SkinChangeParam = Cast<UEventParamSkinChange>(EventParam);
	if(SkinChangeParam)
	{
		ChangeMeshSkin(SkinChangeParam->ChangeSkinIndex);
	}
}

// 선택된 Skin Index 기준으로 SkeletalMesh를 변경해줌
void AShooterGameCharacter::ChangeMeshSkin(int SelectSkinIndex)
{
	if(SelectSkinIndex < SkinMeshes.Num())
	{
		SkinIndex = SelectSkinIndex;
		GetMesh()->SetSkeletalMeshAsset(SkinMeshes[SelectSkinIndex]);
	}
}
```
**IEventListener interface를 상속받아 EventManager에 Listener 등록해준 뒤**
<br>**ChangeSkin Event가 발생되면  OnReceived()를 통해 이벤트와 변경사항을 받아옴**

## 실행 화면
![2024-09-02154512-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/4d0d4886-9416-4cf6-b770-a0aee0544dfa)





