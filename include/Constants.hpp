#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <string>
#include <core/glm/glm.hpp>
#include "World.hpp"

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

const float PLAYER_MAX_SIZE = 0.3;
const float ENEMY_MAX_SIZE = 0.3;
const float PLAYER_BULLET_MAX_SIZE = 0.03;
const float ENEMY_BULLET_MAX_SIZE = 0.03;
const float ITEM_MAX_SIZE = 0.1;

const glm::vec4 PLAYER_COLOR(0.75f, 0.75f, 0.75f, 1.0f);
const glm::vec4 ENEMY_COLOR(1.0f, 0.25f, 0.25f, 1.0f);
const glm::vec4 PLAYER_BULLET_COLOR(1.0f, 0.88f, 0.0f, 1.0f);
const glm::vec4 ENEMY_BULLET_COLOR(1.0f, 0.88f, 0.0f, 1.0f);
const glm::vec4 ITEM_COLOR(1.0f, 0.5f, 0.5f, 1.0f);

const int ENEMY_REGEN_INTERVAL_SECE = 3;

#endif