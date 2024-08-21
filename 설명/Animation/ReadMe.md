# Animation 관련 설정

![Anim3](https://github.com/user-attachments/assets/ac2a70c3-90cb-4d00-8ec9-f4bcbf6d2b9e)

**블렌드 스페이스 제작**<br><br>

![image](https://github.com/user-attachments/assets/1a9c0960-14cb-497c-9ec6-1ccadf4b0b24)

**Speed 0~100, Angle -180 ~ 180값을 설정해서 속도와 방향에 따른 애니메이션이 출력되도록 설정**<br><br>


![image](https://github.com/user-attachments/assets/5f8f6433-b163-41e3-982f-a31bbaccea05)

**애니메이션 블루프린트에서 블랜드 스페이스를 가져와 최종 애니메이션 출력**<br><br>

![image](https://github.com/user-attachments/assets/debe078a-daa0-4c1c-a108-b545dfccaf98)

**Pawn의 Velocity를 받아와 속도를 지정하고 방향 벡터를 받아와 Rotation을 설정해줌**<br><br>
**Inverse Transform Direction : 방향 벡터를 제공된 트랜스폼의 역으로 변환하여 월드 스페이스에서 로컬 스페이스로의 방향 트랜스폼이 됨**<br><br>
**Rotation From X Vector : X(언리얼 정면 방향)을 기준으로 Rotation값을 가져옴**<br><br>
