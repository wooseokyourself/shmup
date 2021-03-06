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
- r: On/Off wireframe rendering.   
- v: Change viewing mode. TPS, FPS, and 2D are supported.   
- t: Diffuse mapping on/off   
- n: Normal mapping on/off   
- 1: Use directional light(sun) and point lights(planetary)   
- 2: Use directional light only
- 3: Use point lights only
- 4: No lighting

3. Files
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
│   ├── gouraud_fragment.frag
│   │   # Gouraud shader.
│   ├── gouraud_vertex.vert
│   │   # Gouraud shader.
│   ├── nonlight_fragment.frag
│   │   # Simple shader.
│   ├── nonlight_vertex.vert
│   │   # Simple shader.
│   ├── phong_fragment.frag
│   │   # Phong shader.
│   └── phong_vertex.vert
│       # Phong shader.
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
│   │   ├── stb
│   │   │    # stb headers.
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
│   ├── Sun.hpp
│   │   # Header for class "Sun".
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
│   ├── Sun.cpp
│   │   # Definitions for class "Sun".
│   └── World.hpp
│       # World definitions and drawing the world.
├── shmup.sln
├── shmup.vcxproj
└── shmup.vcxproj.filters
    # Visual Studio project.