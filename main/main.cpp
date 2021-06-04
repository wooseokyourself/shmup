#define STB_IMAGE_IMPLEMENTATION

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

#include "GamePlay.hpp"

using namespace std;

int lastRenderTime = 0;
bool asyncKeyBuf[256];
std::queue<unsigned char> discreteKeyBuf;

GamePlay* gameplay;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gameplay->renderPerspectiveScene();
    gameplay->renderOrthoScene();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    float widthFactor = (float)width / (float)100;
    float heightFactor = (float)height / (float)100;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0 * widthFactor, 1.0 * widthFactor, -1.0 * heightFactor, 1.0 * heightFactor, -1.0, 1.0);
}

void keyboardDown(unsigned char key, int x, int y) {
    discreteKeyBuf.push(key);
}

void specialKeyboardDown(int key, int x, int y) {
    asyncKeyBuf[key] = true;
}

void specialKeyboardUp(int key, int x, int y) {
    asyncKeyBuf[key] = false;
}

void updateFrame() {
    const int NOW_TIME = glutGet(GLUT_ELAPSED_TIME);
    if (NOW_TIME - lastRenderTime < TIME_PER_FRAME)
        return;
    gameplay->update(asyncKeyBuf, discreteKeyBuf);
    glutPostRedisplay();
    lastRenderTime = NOW_TIME;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH) / 2) - (WINDOW_WIDTH / 2), (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (WINDOW_HEIGHT / 2));
    glutCreateWindow("Assn4");

#ifdef __APPLE__
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
    glewExperimental = GL_TRUE;
#elif _WIN32
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif

    printf("%s\n", glGetString(GL_VERSION));
    printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboardDown);
    glutSpecialFunc(specialKeyboardDown);
    glutSpecialUpFunc(specialKeyboardUp);
    glutIdleFunc(updateFrame);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    gameplay = new GamePlay;
    gameplay->start();
    glutMainLoop();

    return 0;
}