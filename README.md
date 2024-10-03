# ShooterProject
### UE5 기반으로 하는 슈터게임 제작입니다.
### **엔진 : UE5**
### **IDE : Visual Studio Code**<br>

## 진행중인 사항은 아래에서 확인 가능합니다.
### [설명](https://github.com/HongJaehan-hub/ShooterProject/tree/main/%EC%84%A4%EB%AA%85)
### [C++ 코드](https://github.com/HongJaehan-hub/ShooterProject/tree/main/ShooterGame/Source/ShooterGame)

## 현재 제작 진행중

<br>캐릭터 블랜드 스페이스 사용하여 애니메이션 구현
<br>EnhancedInput사용하여 Fire Input 적용
<br>Gun 클래스 생성과 Fire함수 추가<br>

<br>Bullet 생성 후 ProjectileMovementComponent추가 
<br>Bullet 생성 및 사용을 최적화 하기위해ObjectPool 클래스 생성 
<br>ObjectPool로 관리할 Actor 상위 클래스 ObjectPoolActor 클래스 생성 후 사용 
<br>[[ObjectPool 설명]](https://github.com/HongJaehan-hub/ShooterProject/tree/main/%EC%84%A4%EB%AA%85/ObjectPool)

<br> BaseWidget, PopupWidget 제작
<br> PopupWidget 애니메이션 추가
<br> 위 아래 방향으로 쏠 수 있도록 additive animation 추가
<br> UIManager Singleton으로 제작, Popup을 UIManager를 통해 컨트롤 할 수 있도록 구현
<br>[[Animation 설명]](https://github.com/HongJaehan-hub/ShooterProject/tree/main/%EC%84%A4%EB%AA%85/Animation)

<br> Character의 Skin을 변경할 수 있는 Popup을 제작
<br> UIManager를 통해 Parameter을 전달받아 현재 적용중인 스킨 기준으로 팝업을 초기화
<br>[[Widget 설명]](https://github.com/HongJaehan-hub/ShooterProject/tree/main/%EC%84%A4%EB%AA%85/Widget)

<br> Event Manager 제작
<br> 싱글톤으로 제작하고 팝업과 캐릭터의 디커플링을 위하여 이벤트패턴을 구현
<br> 팝업이 닫힐 때 스킨 선택 이벤트를 발생시켜 캐릭터에서 스킨이 변경되도록 구현
<br>[[EventManager 설명]](https://github.com/HongJaehan-hub/ShooterProject/tree/main/%EC%84%A4%EB%AA%85/EventManager)

<br> CMSTable Manager 제작
<br> json 형식의 파일을 기준으로 테이블 제작
<br>[[CMSTable Manager 설명]](https://github.com/HongJaehan-hub/ShooterProject/tree/main/%EC%84%A4%EB%AA%85/LoadContentTable)

<br>![2024-09-09181623-ezgif com-video-to-gif-converter (1)](https://github.com/user-attachments/assets/00d3663a-13b2-41cd-b8e2-cbc050ab1119)
<br> Character Manager 제작, 캐릭터 선택 창 제작
<br> Character.json 파일로부터 데이터를 가져와 캐릭터 선택 기능 추가
<br>[[Character 선택 창 설명]](https://github.com/HongJaehan-hub/ShooterProject/tree/main/%EC%84%A4%EB%AA%85/Character)
