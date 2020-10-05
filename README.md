# KingDB Engine

- [KingDB Engine](#kingdb-engine)
  - [Game Engine for KINGDB Engine](#game-engine-for-kingdb-engine)
    - [Requests for KINGDB Engine](#requests-for-kingdb-engine)
    - [To Do](#to-do)

## Game Engine for KINGDB Engine

Ground Rules

1. Use meson for the build system
2. Use C++17
3. Use OpenGL for the Graphics, and GStreamer/OpenAL for the Audio
4. Use libsodium for encryption and decryption
5. If we don't make a huge disaster, the engine will be multi-threaded

Always welcome for the better repository name

### Requests for KINGDB Engine

1. Windows Platform 타겟
2. 2D 게임
3. png mapping 지원
4. Textbox 시스템 지원(Look To Do Section)
5. BGM, Sound Effect 지원
6. Object 상호작용 지원(Look To Do Section)
7. Map 시스템 관리
8. 키보드 입력 지원 및 키 변경 가능하도록 지원
9. 세이브 / 로드 기능 제공(Slot 3개)
10. 엔진은 동적 라이브러리 형태로 제공되어, 실제 게임을 구현할 때 유연하게 가져다 쓸 수 있어야 함

### To Do

- Map/Scene Object, 해당 Object 관리 및 저장 방안 고민 필요
- Textbox 시스템 어떻게 사용자/개발자 용이하게 할지 고민 필요
  - Skip / 빠르게 보기 확인하는 방안
  - 입력 용이할 수 있도록 : DB 형태로 Text 입력해 두고 설정하는 방식?
- Game Object간의 상호작용 지원 방안 고민할 것
  - Collider?
  - position?
  - Overlapped를 확인 가능한 방법을 고민할 것