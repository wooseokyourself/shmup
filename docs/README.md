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
├── shader
│   ├── fragment.frag
│   │   # Fragment shader.
│   └── vertex.vert
│       # Vertex shader.
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
│   │   │   # Header-only for class "Mesh".
│   │   ├── ModelViewMat.hpp
│   │   │   # Header-only for class "ModelViewMat".
│   │   ├── Object.hpp
│   │   │   # Header-only for class "Object".
│   │   ├── Shader.hpp
│   │   │   # Header-only for class "Shader".
│   │   └── Utility.hpp
│   │       # Header-only top level functions.
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
└── shmup.vcxproj
    # Visual Studio project.
```

# Example Screen
<img width="828" alt="example" src="https://user-images.githubusercontent.com/49421142/117574832-f228f000-b119-11eb-9879-0ce65f51a913.png">    
<img width="828" alt="example" src="https://user-images.githubusercontent.com/49421142/117574833-f3f2b380-b119-11eb-9736-d9642928d0fa.png">    
<img width="828" alt="example" src="https://user-images.githubusercontent.com/49421142/117574836-f523e080-b119-11eb-8ac6-715d38a0adfb.png">    
<img width="828" alt="example" src="https://user-images.githubusercontent.com/49421142/117574837-f6eda400-b119-11eb-8b70-f6f39bf023ca.png">

# Resources

[The Open Asset Import Library (assimp)](https://github.com/assimp/assimp)   
[Learn OpenGL](https://learnopengl.com)   
[Player Aircraft Model (“assets/models/player.obj”)](https://www.cgtrader.com/free-3d-models/aircraft/jet/f-15-c-eagle)   
[Enemy Aircraft Model (“assets/models/ebm314.obj”)](https://www.cgtrader.com/free-3d-models/aircraft/military/emb-314-super-tucano)   
[Ammo Crate Model (“assets/models/ammo_crate.obj”)](https://www.cgtrader.com/free-3d-models/military/other/ammo-crate-pbr-lowpoly)   
[Heart Model (“assets/models/love.obj”)](https://www.cgtrader.com/free-3d-models/character/anatomy/love-low-poly)   
[Sphere Model (“assets/models/sphere.obj”)](https://www.cgtrader.com/free-3d-models/space/other/sphere-de6c0ee5-444a-4b26-afd3-37b4880601a0)   
[3D Texts Models ("assets/models/text3d_*")](http://profilki.pl/en/generators/3d-texts)