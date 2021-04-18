#ifndef __WORLD__
#define __WORLD__

#include <core/GL/glew.h>
#include <core/GL/freeglut.h>
#include <core/glm/glm.hpp>

const float AXIS_LIMIT_ABS = 3.0f; // 표현되는 축의 범위를 [-3.0,3.0] 으로 정의
const float WORLD_LIMIT_ABS = 1.0f; // 게임월드
const int TILE_N = 90; // 전체 타일의 수는 TILE_N ^ 2
const float TILE_LEN = (AXIS_LIMIT_ABS * 2.0f) / (float)TILE_N;

void drawGrid();

#endif