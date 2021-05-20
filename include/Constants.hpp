#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <string>
#include <core/glm/glm.hpp>
#include "World.hpp"

const int FPS = 60;
const int TIME_PER_FRAME = 1000 / FPS;

namespace AircraftSpeed {
    const float FAST = 0.015;
    const float NORMAL = 0.010;
    const float SLOW = 0.005;
};

namespace BulletSpeed {
    const float FAST = 0.05;
    const float NORMAL = 0.03;
    const float SLOW = 0.01;
};

const int PLAYER_LIVES = 3;
const int MAX_STAGE = 5;

const float WINDOW_WIDTH = 1280.0f;
const float WINDOW_HEIGHT = 720.0f;
const float WINDOW_FACTOR = 1000.0f;

const float AXIS_LIMIT_ABS = 9.0f;
const float WORLD_LIMIT_ABS = 3.0f;
const int TILE_N = 90; // 전체 타일의 수는 TILE_N ^ 2
const float TILE_LEN =(AXIS_LIMIT_ABS * 2.0f) /(float)TILE_N;
const glm::vec4 WORLD_GROUND_COLOR(0.05f, 0.05f, 0.05f, 1.0f);

const float UI_MIN_X = -(WINDOW_WIDTH / WINDOW_FACTOR); 
const float UI_MAX_X = WINDOW_WIDTH / WINDOW_FACTOR;
const float UI_Y = AXIS_LIMIT_ABS;
const float UI_Y_HALF_ABS = 1.0f;
const float UI_Z = -1.0f;

const float UI_CAM_X = 0.0f;
const float UI_CAM_Y = UI_Y;
const float UI_CAM_Z = 1.0f;

namespace PLAYER_FRAME {
    const glm::vec3 UP(0.0f, 1.0f, 0.0f);
    const glm::vec3 LEFT(1.0f, 0.0f, 0.0f);
    const glm::vec3 FRONT(0.0f, 0.0f, 1.0f);
};

const glm::vec3 PLAYER_INIT_POS(0.0f, WORLD_LIMIT_ABS * 0.1f, WORLD_LIMIT_ABS);
const glm::vec3 ENEMY_INIT_POS(0.0f, WORLD_LIMIT_ABS * 0.1f, -WORLD_LIMIT_ABS);
// const glm::vec3 PLANETARY_A_POS(-WORLD_LIMIT_ABS * 1.3f, WORLD_LIMIT_ABS * 0.7f, -WORLD_LIMIT_ABS * 2.0f);
const glm::vec3 PLANETARY_A_POS(0.0f, WORLD_LIMIT_ABS * 0.1f, 0.0f);
const glm::vec3 PLANETARY_B_POS(WORLD_LIMIT_ABS * 0.8f, WORLD_LIMIT_ABS * 0.4f, -WORLD_LIMIT_ABS * 0.7f);

const float PLAYER_MAX_SIZE = 0.3;
const float ENEMY_MAX_SIZE = 0.3;
const float PLAYER_BULLET_MAX_SIZE = 0.03;
const float ENEMY_BULLET_MAX_SIZE = 0.03;
const float ITEM_MAX_SIZE = 0.1;
const float PLANETARY_A_MAX_SIZE = 0.5f;
const float PLANETARY_B_MAX_SIZE = 0.3f;

const glm::vec4 PLAYER_COLOR(0.75f, 0.75f, 0.75f, 1.0f);
const glm::vec4 ENEMY_COLOR(1.0f, 0.25f, 0.25f, 1.0f);
const glm::vec4 PLAYER_BULLET_COLOR(1.0f, 0.88f, 0.0f, 1.0f);
const glm::vec4 ENEMY_BULLET_COLOR(1.0f, 0.88f, 0.0f, 1.0f);
const glm::vec4 ITEM_COLOR(1.0f, 0.5f, 0.5f, 1.0f);

const int ENEMY_REGEN_INTERVAL_SECE = 3;

enum gameMode {
    GAMEMODE_NONE,
    GAMEMODE_ALL_PASS,
    GAMEMODE_ALL_FAIL
};

enum viewMode { 
    VIEWMODE_TPS,
    VIEWMODE_FPS,
    VIEWMODE_2D
};

#endif