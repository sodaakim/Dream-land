# Dream Land (Unreal Project)

![image](https://github.com/sodaakim/Dream-land/assets/83997634/ebf89636-9f42-489e-90df-62bffeb46e49)

- 본 프로젝트는 언리얼 엔진을 활용하여 작은 RPG시스템을 구축하는 것을 목표로 진행하고 있습니다.
- 모든 로직을 c++로 구현을 목표로 하고 있습니다.

#
지형과 지역, 캐릭터, 이벤트
![Uploading image.png…]()

- 지역은 기본적으로 넓은 초원이 펼쳐진 아늑한 환경에서, 여러가지 지역으로 구분된 맵으로 구성한다.
- 초원에는 기본 마을이 존재한다.
- npc가 존재한다. npc는 각기 다른 직업을 가지고 있고, 퀘스트를 주거나 물건을 판매하거나 대화를 진행할 수 있다.
- npc는 자유롭게 움직이고 있다.
- 지역에 진입하면 해당 지역 이름을 상단에 출력한다.
- 날씨와 시간 : 비가 오고, 눈이 내리는 이벤트가 발생한다. Day/Night을 구현한다.
- 멀티 플레이를 기본으로 하고, 플레이어가 많을 경우 월드 텍스처 깨짐 현상을 해결해야한다.

#
npc와의 대화 로직 제작
![image](https://github.com/sodaakim/Dream-land/assets/83997634/e1b81f22-1bb4-4b5a-9105-1ce0b60b3f03)
![image](https://github.com/sodaakim/Dream-land/assets/83997634/98fc6802-61db-4d25-b226-1bd7c9fca6d3)

- 각 npc는 인사말, 기본 대화가 있고, 퀘스트가 주어지면 특별 대화를 할 수 있다
- npc와 interact : NPC와 오버랩 후 E키를 누르면 대화 또는 상점 버튼을 누를 수 있다.
- 인사말 : interact시 npc의 이름과 인사말을 볼 수 있다.
- 플레이어에게는 대화 중 선택지가 주어지고, 각기 다른 결과를 도출한다.

#
퀘스트 시스템 제작
![image](https://github.com/sodaakim/Dream-land/assets/83997634/90d75460-93ce-4aca-a8b3-3e4fc02dfd18)

- 퀘스트 종류에는 메인 퀘스트와 서브 퀘스트, 이벤트 퀘스트가 존재한다.
- 퀘스트 발동 조건과 보상, 그리고 퀘스트 진행 로직이 포함된다.
- 각 플레이어의 퀘스트 진행도를 확인할 수 있는 퀘스트 관리자 모드가 존재한다.

#
아이템 시스템 제작
![image](https://github.com/sodaakim/Dream-land/assets/83997634/8142400e-8e21-4b86-9e46-6f75aad1144e)

- 아이템 구조체가 존재하고, 월드에 존재하는 아이템을 관리하는 시스템이 존재한다.
- 아이템을 줍거나 버릴 수 있고, 아이템에는 네임 태그가 존재한다.
- 퀘스트 아이템이 존재한다.
- 아이템의 추가 속성을 툴팁으로 확인할 수 있다.

#
npc와의 상점 시스템 제작
![image](https://github.com/sodaakim/Dream-land/assets/83997634/72567fae-7912-4137-ad54-97d7f939d863)

- npc는 각기 다른 아이템을 판매한다.
- 아이템 시스템으로부터 불러와 관리한다.
- 판매하는 아이템은 이벤트에 따라 수량과 종류가 달라지며, 플레이어가 아이템을 구매하면 구매 가능 수량이 줄어든다.

#
인벤토리 시스템 제작
- 5*5칸의 기본 인벤토리가 제공되고, 인벤토리에는 한칸에 한개의 물품을 넣을 수 있다.
- 가능하다면 여러 칸에 여러 크기의 물픔을 배치할 수 있도록 시스템을 확장하고 싶다.
- 인벤토리는 같은 아이템의 경우 스택되어 저장되고, 아이템이 추가되거나 버려지면 인벤토리를 업데이트한다.
- 인벤토리에서 아이템의 이미지와 이름, 수량, 가격을 확인할 수 있다.
- 툴팁으로 아이템의 추가 정보를 확인할 수 있다.

#
사냥 시스템 제작
![image](https://github.com/sodaakim/Dream-land/assets/83997634/580a9fff-d5ed-4b73-b872-6a2228d9511f)

- 동물들은 자유롭게 움직이고 있다.
- 동물들은 각자 체력이 존재하고, 체력이 소진될 경우 소멸된다.
- 동물들은 각자 보유한 드랍 아이템 리스트 중 일부에 대해 랜덤 드랍하고, 플레이어는 아이템을 수집할 수 있다.
- 플레이어의 사냥을 위한 애니메이션을 수정한다.
- 플레이어는 체력이 존재하고, 체력이 모두 소진되면 체력을 비축하기 전까지 사냥을 할 수 없다.
