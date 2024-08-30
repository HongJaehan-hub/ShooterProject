# ShooterProject
UE5 기반으로 하는 슈터게임 제작입니다.

## 진행중인 사항은 아래에서 확인 가능합니다.
[설명](https://github.com/HongJaehan-hub/ShooterProject/tree/main/%EC%84%A4%EB%AA%85).

## 현재 제작 진행중

**2024.08.24**
<br>캐릭터 블랜드 스페이스 사용하여 애니메이션 구현

<br>**2024.08.23**
<br>EnhancedInput사용하여 Fire Input 적용
<br>Gun 클래스 생성과 Fire함수 추가<br>

<br>**2024.08.25**
<br>Bullet 생성 후 ProjectileMovementComponent추가 
<br>Bullet 생성 및 사용을 최적화 하기위해ObjectPool 클래스 생성 
<br>ObjectPool로 관리할 Actor 상위 클래스 ObjectPoolActor 클래스 생성 후 사용 

<br>**2024.08.26**
<br> BaseWidget, PopupWidget 제작
<br> PopupWidget 애니메이션 추가

<br>**2024.08.28**
<br> 위 아래 방향으로 쏠 수 있도록 additive animation 추가
<br> UIManager Singleton으로 제작, Popup을 UIManager를 통해 컨트롤 할 수 있도록 구현
