#include "World.hpp"

void drawWorld() {
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    float z = -AXIS_LIMIT_ABS;
    bool flag = true;
    int vertexCount = 0;
    glColor3f(0.5f, 0.5f, 0.5f);
    while (z <= AXIS_LIMIT_ABS) {
        float x = -AXIS_LIMIT_ABS;
        glBegin(GL_TRIANGLE_STRIP);
        while (x <= AXIS_LIMIT_ABS) {
            glVertex3f(x, 0.0f, z);
            vertexCount ++;
            if (flag) { // 밑으로
                z += TILE_LEN;
            }
            else { // 위로
                x += TILE_LEN;
                z -= TILE_LEN;
            }
            if (x > AXIS_LIMIT_ABS)
                z += TILE_LEN;
            flag = !flag;
        }
        glEnd();
    }

    // x axis (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-WORLD_LIMIT_ABS, 0.0f, 0.0f);
    glVertex3f(WORLD_LIMIT_ABS, 0.0f, 0.0f);
    glEnd();

    // z axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0f, 0.0f, -WORLD_LIMIT_ABS);
    glVertex3f(0.0f, 0.0f, WORLD_LIMIT_ABS);
    glEnd();

    // bound of game world (green)
    const int WORLD_TILE_N = TILE_N / 3;
    const int offset = WORLD_TILE_N / 2;
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-TILE_LEN * float(offset), 0.0f, -TILE_LEN * float(offset));
    glVertex3f(-TILE_LEN * float(offset), 0.0f, TILE_LEN * float(offset));
    glVertex3f(TILE_LEN * float(offset), 0.0f, TILE_LEN * float(offset));
    glVertex3f(TILE_LEN * float(offset), 0.0f, -TILE_LEN * float(offset));
    glEnd();
}