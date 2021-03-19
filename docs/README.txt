1. How to Run

1.1. Requirements: Visual Studio 2019 for C++ Desktop

1.2. Compile and Run
1.2.1. Double click file shmup.vcxproj to open the project in Visual Studio 2019.
1.2.2. Click Build --> Build Solution , or press F7
1.2.3. Click Debug --> Run without Debug , or press Ctrl + F5

2. Instructions
- ←↑→↓: Move player.
- Space Bar: Fire a bullet.
- c: The player becomes invincible, and the enemy dies in one shot.
- f: Players cannot fire bullets, and the game is over as soon as an enemy bullet is hit.

3. Files
.
├── docs
├── bin
│   # OpenGL binaries.
├── lib
│   # OpenGL libraries.
├── main
│   └── main.cpp
│       # Main function for this project.
├── include
│   ├── GL
│   │   # OpenGL headers.
│   ├── glm
│   │   # glm headers.
│   ├── base
│   │   ├── DynamicObject.hpp
│   │   │   # Header for class "DynamicObject".
│   │   ├── ModelViewMat2D.hpp
│   │   │   # Header for class "ModelViewMat2D".
│   │   ├── Point2D.hpp
│   │   │   # Header for class "Point2D".
│   │   ├── Rect.hpp
│   │   │   # Header for class "Rect".
│   │   └── Rgb.hpp
│   │       # Header for class "Rgb".
│   ├── dynamics
│   │   ├── Airplane.hpp
│   │   │   # Header for class "Airplane" and "BulletManager".
│   │   └── Bullet.hpp
│   │       # Header for class "Bullet".
│   └── gameplay
│       ├── Ai.hpp
│       │   # Header for class "Ai".
│       ├── Constants.hpp
│       │   # Definitions of constants.
│       └── GamePlay.hpp
│           # Header for class "GamePlay"
├── src
│   ├── base
│   │   ├── DynamicObject.cpp
│   │   │   # Definitions for class "DynamicObject".
│   │   ├── ModelViewMat2D.cpp
│   │   │   # Definitions for class "ModelViewMat2D".
│   │   └── Rect.cpp
│   │       # Definitions for class "Rect".
│   ├── dynamics
│   │   ├── Airplane.cpp
│   │   │   # Definitions for class "Airplane" and "BulletManager.
│   │   └── Bullet.cpp
│   │       # Definitions for class "Bullet".
│   └── gameplay
│       ├── Ai.cpp
│       │   # Definitions for class "Ai".
│       └── GamePlay.cpp
│           # Definitions for class "GamePlay".
│
├── shmup.sln
├── shmup.vcxproj
├── shmup.vcxproj.filters
└── shmup.vcxproj.user
    # Visual Studio project.