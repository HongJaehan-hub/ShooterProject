# Widget 작업
## Base Popup
[UPopupWidget.h](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/Widget/PopupWidget.h).
<br>[UPopupWidget.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/Widget/PopupWidget.cpp)

![2024-08-27214402-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/e048e15f-2969-4217-96b1-3f02484d7fc1)
<br> Popup이 자연스럽게 열리게 하기 위해 애니메이션 제작 Alpha와 Offset 조정

```
USTRUCT(BlueprintType)
struct FPopupParam
{
    GENERATED_BODY()

public:
	FPopupParam(){};
};
```
**Popup을 초기화 해줄 struct 생성**<br><br>

```
UFUNCTION(BlueprintCallable)
virtual void OnInit(FPopupParam Param = FPopupParam());
```
**UPopupWidget을 상속받는 곳에서 Open을 재정의 해서 초기화**



# UIManager
[UIManager.h](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/UIManager.h).
<br>[UIManager.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/UIManager.cpp)<br>

**Singleton으로 Instance에 접근해 사용하도록 구현**
```
UUIManager *UUIManager::Instance()
{
    if(_Instance == nullptr)
    {
        _Instance = NewObject<UUIManager>();
        _Instance->AddToRoot(); // GC 방지
    }
    return _Instance;
}
```

<br>**Popup을 열어줄 때 각 하위 Popup에서 필요한 Param의 struct를 받을 수 있도록 Param도 template으로 구현**
```
template <typename T, typename TParam>
inline T *UUIManager::OpenPopup(UObject *WorldContextObject, const FString &WidgetName, TParam &PopupParam)
{
	static_assert(TIsDerivedFrom<T, UPopupWidget>::Value, "must be derived from UPopupWidget");

	UUserWidget* Widget = CreateWidget(WorldContextObject, WidgetName);
    if(Widget)
    {
        Widget->AddToViewport();
        WidgetStack.Add(Widget);

		T* PopupWidget = Cast<T>(Widget);
		if(PopupWidget)
		{
			PopupWidget->OnInit(PopupParam);
			PopupWidget->Open();
		}
		return PopupWidget;
    }

    return nullptr;
}
```

<br><br>**template Interface 제작 후 Param필요한 곳에서 사용**
```
// 템플릿 인터페이스 정의
template<typename TParam>
class IPopupInterface
{
public:
    virtual void OnInit(TParam Param) = 0;
};
```

<br><br>**Param Interface 사용 부분**
```
//////////////////// Interface 정의////////////////////////////////////
USTRUCT(BlueprintType)
struct FChangeSkinPopupParam : public FPopupParam
{
    GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 SelectSkinIndex = 0;

	FChangeSkinPopupParam(){};
	FChangeSkinPopupParam(int32 SelectIndex) : SelectSkinIndex(SelectIndex) {};
};

UCLASS()
class SHOOTERGAME_API USkinChangePopupWidget : public UPopupWidget, public IPopupInterface<FChangeSkinPopupParam> // Interface 상속받음
{
	GENERATED_BODY()

public:
	virtual void OnInit(FChangeSkinPopupParam Param = FChangeSkinPopupParam()); // OnInit호출 시 FChangeSkinPopupParam 받을 수 있음
};

//////////////////// 실제 호출 부분/////////////////////////////
void AShooterPlayerController::OnOpenPopup(const FInputActionValue& Value)
{
    // check already opened widget
    if(!UUIManager::Instance()->IsWidgetOpened("WBP_SkinChangePopup"))
    {
        auto ShooterCharacter = Cast<AShooterGameCharacter>(GetCharacter());
        if(ShooterCharacter)
        {
            // 열어줄 팝업의 Param struct를 가져와서 초기화 후 UIManager에 Param전달
            // 현재 캐릭터에 접근해서 적용중인 스킨의 Index값을 받아와서 초기화
            FChangeSkinPopupParam Param = FChangeSkinPopupParam(ShooterCharacter->GetCurrentSkinIndex());
            UUIManager::Instance()->OpenPopup<USkinChangePopupWidget, FChangeSkinPopupParam>(GetPawn(), "WBP_SkinChangePopup", Param);
            SetUIMode(true);
        }
    }
}
```
<br>

![2024-09-01163817-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/55c0a9b2-3794-4838-bf51-59685fe8d21f)
<br>**팝업 오픈 시 현재 캐릭터의 적용중인 SkinSlotIndex를 받아와
<br>해당 정보 기반으로 팝업을 초기화 시켜줌 (현재 첫번째 스킨 적용중)**

