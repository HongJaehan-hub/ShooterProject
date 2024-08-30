# Widget 작업
## Base Popup
[UBasePopupWidget.h](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/Widget/PopupWidget.h).
<br>[UBasePopupWidget.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/Widget/PopupWidget.cpp)

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
**Popup을 초기화 해줄 struct 생성**<br>

```
	UFUNCTION(BlueprintCallable)
	virtual void Open(const FPopupParam& param = FPopupParam());
```
**UPopupWidget을 상속받는 곳에서 Open을 재정의 해서 초기화**



# UIManager
[UIManager.h](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/UIManager.h).
<br>[UIManager.cpp](https://github.com/HongJaehan-hub/ShooterProject/blob/main/ShooterGame/Source/ShooterGame/UIManager.cpp)<br>

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
**Singleton으로 Instance에 접근해 사용하도록 구현**<br>

```
template <typename T>
inline T *UUIManager::OpenPopup(UObject *WorldContextObject, const FString &WidgetName, FPopupParam PopupParam)
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
  		PopupWidget->Open(PopupParam);
	}
	return PopupWidget;
    }

    return nullptr;
}
```
**template 반환 형태로 만들어 UPopupWidget을 상속받은 UserWidget만 열수 있도록 구현**

![2024-08-30212120-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/0ceecba9-36e2-4d75-8b5a-dd3a7bfa3a52)
<br>**Popup 오픈 테스트**
<br>팝업 오픈 시 캐릭터 컨트롤용 MappingContext를 제거해 입력을 마우스로만 제한 (팝업 닫을 시 다시 Add 해줌)

