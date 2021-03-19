# How to Run

## Windows (x64)
### Requirements
+ Visual Studio 2019 for C++ Desktop

### Compile and Run
1. Double click file ```shmup.vcxproj``` to open the project in Visual Studio 2019.
2. Click ```Build --> Build Solution``` , or press ```F7```
3. Click ```Debug --> Run without Debug``` , or press ```Ctrl + F5```

## macOS
### Requirements
+ Visual Studio Code
+ [XQuartz](https://www.xquartz.org)
+ glew, glut, and glm installation with homebrew
```console
mac@mac~ $ brew install glew
mac@mac~ $ brew install glut
mac@mac~ $ brew install glm
```
### Compile and Build
1. In Visual Studio Code, open this project repository.
2. Click ```Terminal --> Run Build Task..``` , or press ```Shift + Cmd + b```
3. Run ```./app``` in terminal or double click ```app``` file to run.


# Instructions
+ ``` ←↑→↓ ```: Move player.
+ ``` Space Bar ```: Fire a bullet.
+ ``` c ```: The player becomes invincible, and the enemy dies in one shot.
+ ``` f ```: Players cannot fire bullets, and the game is over as soon as an enemy bullet is hit.

# Files
```shell
.
├── LICENSE
├── docs
│   ├── README.md
│   └── doxygen
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
│   │   └── Rgba.hpp
│   │       # Header for class "Rgba".
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
├── .vscode
│   # Visual Studio Code project for macOS.
│
├── shmup.sln
├── shmup.vcxproj
├── shmup.vcxproj.filters
└── shmup.vcxproj.user
    # Visual Studio project.
```

# Example Screen
<img width="828" alt="example" src="https://user-images.githubusercontent.com/49421142/111774009-38b85600-88f2-11eb-9250-887b48e16cc9.png">