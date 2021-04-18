#include <iostream>
#include <vector>
#include <queue>

#include "GamePlay.hpp"

using namespace std;

const float WINDOW_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 800.0f;

int lastRenderTime = 0;
bool asyncKeyBuf[256];
std::queue<unsigned char> discreteKeyBuf;

static GamePlay gameplay;

/** @brief GLUT callback. */
void display () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gameplay.render();
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glutSwapBuffers();
}

/** @brief GLUT callback. */
void reshape (int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat base = WINDOW_HEIGHT < WINDOW_WIDTH ? WINDOW_HEIGHT : WINDOW_WIDTH;
    GLfloat widthset = WINDOW_WIDTH / base;
    GLfloat heightset = WINDOW_HEIGHT / base;
    gluPerspective(60, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 1000.0f);  
}

void keyboardDown (unsigned char key, int x, int y) {
    discreteKeyBuf.push(key);
}

void specialKeyboardDown (int key, int x, int y) {
    asyncKeyBuf[key] = true;
}

void specialKeyboardUp (int key, int x, int y) {
    asyncKeyBuf[key] = false;
}

void updateFrame () {
    const int NOW_TIME = glutGet(GLUT_ELAPSED_TIME);
    gameplay.update(asyncKeyBuf, discreteKeyBuf);
    glutPostRedisplay();
    lastRenderTime = NOW_TIME;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH) / 2) - (WINDOW_WIDTH / 2), (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (WINDOW_HEIGHT / 2));
    glutCreateWindow("Assn3-1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);    
    glDepthFunc(GL_LEQUAL);
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboardDown);
    glutSpecialFunc(specialKeyboardDown);
    glutSpecialUpFunc(specialKeyboardUp);
    glutIdleFunc(updateFrame);

    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    
    gameplay.start();
    glutMainLoop();

    return 0;
}