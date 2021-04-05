# How to Run

## Windows (x64)
### Requirements
+ Visual Studio 2019 for C++ Desktop

### Compile and Run
1. Double click file ```shmup.vcxproj``` to open the project in Visual Studio 2019.
2. Click ```Build --> Build Solution``` , or press ```F7```
3. Click ```Debug --> Run without Debug``` , or press ```Ctrl + F5```

# Instructions
+ ``` ←↑→↓ ```: Move player.
+ ``` Space Bar ```: Fire a bullet.
+ ``` c ```: The player becomes invincible, and the enemy dies in one shot.
+ ``` f ```: Players cannot fire bullets, and the game is over as soon as an enemy bullet is hit.

# Files
```shell
.
├── docs
│   ├── README.md
│   └── README.txt
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
│   │   ├── Object.hpp
│   │   └── core
│   │       ├── BaseRect.hpp
│   │       │   # Header for class "BaseRect".
│   │       ├── Circle.hpp
│   │       │   # Header for class "Circle".
│   │       ├── Figure.hpp
│   │       │   # Header for class "Figure".
│   │       ├── Point2D.hpp
│   │       │   # Header for class "Point2D".
│   │       ├── Rect.hpp
│   │       │   # Header for class "Rect".
│   │       ├── Rgba.hpp
│   │       │   # Header for class "Rgba".
│   │       ├── Text.hpp
│   │       │   # Header for class "Text".
│   │       ├── TransformMatrix.hpp
│   │       │   # Header for class "TransformMatrix".
│   │       ├── Triangle.hpp
│   │       │   # Header for class "Triangle".
│   │       └── Utility.hpp
│   │           # Top level functions.
│   ├── entity
│   │   ├── Airplane.hpp
│   │   │   # Header for class "Airplane".
│   │   ├── Bullet.hpp
│   │   │   # Header for class "Bullet".
│   │   ├── Heart.hpp
│   │   │   # Header for class "Heart".
│   │   ├── Item.hpp
│   │   │   # Header for class "Item".
│   │   ├── Planetary.hpp
│   │   │   # Header for class "Planetary".
│   │   ├── ThirdObjectManager.hpp
│   │   │   # Header for class "ThirdObjectManager".
│   │   └── Ui.hpp
│   │       # Header for class "Ui".
│   └── gameplay
│       ├── Ai.hpp
│       │   # Header for class "Ai".
│       ├── Constants.hpp
│       │   # Definitions of constants.
│       └── GamePlay.hpp
│           # Header for class "GamePlay"
├── src
│   ├── base
│   │   └── Object.cpp
│   │       # Definitions for class "Object".
│   ├── entity
│   │   ├── Airplane.cpp
│   │   │   # Definitions for class "Airplane".
│   │   ├── Bullet.cpp
│   │   │   # Definitions for class "Bullet".
│   │   ├── Heart.cpp
│   │   │   # Definitions for class "Heart".
│   │   ├── Item.cpp
│   │   │   # Definitions for class "Item".
│   │   ├── Planetary.cpp
│   │   │   # Definitions for class "Planetary".
│   │   ├── ThirdObjectManager.cpp
│   │   │   # Definitions for class "ThirdObjectManager".
│   │   └── Ui.cpp
│   │       # Definitions for class "Ui".
│   └── gameplay
│       ├── Ai.cpp
│       │   # Definitions for class "Ai".
│       └── GamePlay.cpp
│           # Definitions for class "GamePlay".
├── shmup.sln
├── shmup.vcxproj
├── shmup.vcxproj.filters
└── shmup.vcxproj.user
    # Visual Studio project.
```

# Example Screen
<img width="1052" alt="example" src="https://user-images.githubusercontent.com/49421142/113574890-fb74f780-9657-11eb-8bb5-d02b0db5b852.png">