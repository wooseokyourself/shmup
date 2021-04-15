#ifndef __WORLD__
#define __WORLD__

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

const float AXIS_LIMIT_ABS = 3.0f; // 표현되는 축의 범위를 [-3,3] 으로 정의
const float WORLD_LIMIT_ABS = 1.0f; // 게임월드는 [-1, 1]
const int TILE_N = 90; // 전체 타일의 수는 TILE_N ^ 2
const float TILE_LEN = (AXIS_LIMIT_ABS * 2.0f) / (float)TILE_N;

void drawGrid();

#endif