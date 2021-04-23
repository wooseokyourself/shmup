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
+ ``` r ```: On/Off wireframe rendering.   
+ ``` v ```: Change viewing mode. TPS, FPS, and 2D are supported.

# Files
```shell
.
├── docs
│   ├── README.md
│   └── README.txt
├── assets
│   └── models
│       # Model files.
├── bin
│   # Binaries of assimp, GL, and glm.
├── lib
│   # Libraries of of assimp, GL, and glm.
├── main
│   └── main.cpp
│       # Main function for this project.
├── include
│   ├── core
│   │   ├── assimp
│   │   │   # assimp headers.
│   │   ├── GL
│   │   │   # OpenGL headers.
│   │   ├── glm
│   │   │    # glm headers.
│   │   ├── Mesh.hpp
│   │   │   # Header for class "Mesh".
│   │   ├── Object.hpp
│   │   │   # Header for class "Object".
│   │   └── Utility.hpp
│   │           # Top level functions.
│   ├── Ai.hpp
│   │   # Header for class "Ai".
│   ├── Aircraft.hpp
│   │   # Header for class "Aircraft".
│   ├── Constants.hpp
│   │   # Constant variables.
│   ├── GamePlay.hpp
│   │   # Header for class "GamePlay"
│   ├── Hud.hpp
│   │   # Header for class "Hud".
│   ├── Planetary.hpp
│   │   # Header for class "Planetary".
│   ├── StraightMovingObjectManager.hpp
│   │   # Header for class "StraightMovingObjectManager".
│   └── World.hpp
│       # World definitions and drawing the world.
├── src
│   ├── Ai.hpp
│   │   # Definitions for class "Ai".
│   ├── Aircraft.hpp
│   │   # Definitions for class "Aircraft".
│   ├── GamePlay.hpp
│   │   # Definitions for class "GamePlay"
│   ├── Hud.hpp
│   │   # Definitions for class "Hud".
│   ├── Planetary.hpp
│   │   # Definitions for class "Planetary".
│   ├── StraightMovingObjectManager.hpp
│   │   # Definitions for class "StraightMovingObjectManager".
│   └── World.hpp
│       # World definitions and drawing the world.
├── shmup.sln
├── shmup.vcxproj
├── shmup.vcxproj.filters
└── shmup.vcxproj.user
    # Visual Studio project.
```

# Example Screen
<img width="828" alt="example" src="https://user-images.githubusercontent.com/49421142/115849759-29cc4280-a460-11eb-8426-9ac54d2dab0d.png">    
<img width="828" alt="example" src="https://user-images.githubusercontent.com/49421142/115839161-57f85500-a455-11eb-882e-4ece20daba58.png">    
<img width="828" alt="example" src="https://user-images.githubusercontent.com/49421142/115839169-59c21880-a455-11eb-8ea7-0bdfc852d563.png">    
<img width="828" alt="example" src="https://user-images.githubusercontent.com/49421142/115839175-5a5aaf00-a455-11eb-814c-0fb30d210253.png">

# Resources

[The Open Asset Import Library (assimp)](https://github.com/assimp/assimp)   
[Player Aircraft Model (“assets/models/player.obj”)](https://www.cgtrader.com/free-3d-models/aircraft/jet/f-15-c-eagle)   
[Enemy Aircraft Model (“assets/models/ebm314.obj”)](https://www.cgtrader.com/free-3d-models/aircraft/military/emb-314-super-tucano)   
[Ammo Crate Model (“assets/models/ammo_crate.obj”)](https://www.cgtrader.com/free-3d-models/military/other/ammo-crate-pbr-lowpoly)   
[Heart Model (“assets/models/love.obj”)](https://www.cgtrader.com/free-3d-models/character/anatomy/love-low-poly)   
[Sphere Model (“assets/models/sphere.obj”)](https://www.cgtrader.com/free-3d-models/space/other/sphere-de6c0ee5-444a-4b26-afd3-37b4880601a0)   