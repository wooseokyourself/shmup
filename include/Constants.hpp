#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <string>
#include <core/glm/glm.hpp>
#include "World.hpp"

const float WINDOW_WIDTH = 1280.0f;
const float WINDOW_HEIGHT = 720.0f;

const float AXIS_LIMIT_ABS = 6.0f;
const float WORLD_LIMIT_ABS = 2.0f;
const int TILE_N = 90; // 전체 타일의 수는 TILE_N ^ 2
const float TILE_LEN = (AXIS_LIMIT_ABS * 2.0f) / (float)TILE_N;

const float UI_MIN_X = -1.0f; 
const float UI_MAX_X = 1.0f;
const float UI_MIN_Y = AXIS_LIMIT_ABS;
const float UI_MAX_Y = AXIS_LIMIT_ABS + 1.0f;
const float UI_MIN_Z = -1.0f;
const float UI_MAX_Z = 1.0f;

const int VIEWMODE_TPS = 0;
const int VIEWMODE_FPS = 1;
const int VIEWMODE_2D = 2;

const std::string PLAYER_MODEL = "assets/models/player.obj";
const std::string ENEMY_MODEL = "assets/models/ebm314.obj";
const std::string BULLET_MODEL = "assets/models/sphere.obj";
const std::string ITEM_MODEL = "assets/models/ammo_crate.obj";

namespace PLAYER_FRAME {
    const glm::vec3 UP(0.0f, 1.0f, 0.0f);
    const glm::vec3 LEFT(1.0f, 0.0f, 0.0f);
    const glm::vec3 FRONT(0.0f, 0.0f, 1.0f);
};

const glm::vec3 PLAYER_INIT_POS(0.0f, WORLD_LIMIT_ABS * 0.1f, WORLD_LIMIT_ABS);
const glm::vec3 ENEMY_INIT_POS(0.0f, WORLD_LIMIT_ABS * 0.1f, -WORLD_LIMIT_ABS);
const glm::vec3 PLANETARY_A_POS(-WORLD_LIMIT_ABS * 1.3f, WORLD_LIMIT_ABS * 0.7f, -WORLD_LIMIT_ABS * 2.0f);
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

#endif