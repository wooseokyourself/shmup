#include <iostream>
#include <vector>
#include <queue>

#include "World.hpp"
#include "Object.hpp"

using namespace std;

namespace Window {
    const float WINDOW_WIDTH = 800;
    const float WINDOW_HEIGHT = 800;
}
int lastRenderTime = 0;
bool asyncKeyBuf[256];
std::queue<unsigned char> discreteKeyBuf;

glm::vec3 camPos = glm::vec3(0.0f, 0.5f, 3.0f);
glm::vec3 at = glm::vec3(0.0f, 0.0f, -5.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

Object player("bin/models/teapot.obj");

/** @brief GLUT callback. */
void display () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camPos.x, camPos.y, camPos.z, at.x, at.y, at.z, camUp.x, camUp.y, camUp.z);

    // gameplay.render();
    drawGrid();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    player.draw();
    glutSwapBuffers();
}

/** @brief GLUT callback. */
void reshape (int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat base = Window::WINDOW_HEIGHT < Window::WINDOW_WIDTH ? Window::WINDOW_HEIGHT : Window::WINDOW_WIDTH;
    GLfloat widthset = Window::WINDOW_WIDTH / base;
    GLfloat heightset = Window::WINDOW_HEIGHT / base;
    gluPerspective(60, Window::WINDOW_WIDTH / Window::WINDOW_HEIGHT, 0.0f, 1.0f);  
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
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
    glutPostRedisplay();
    lastRenderTime = NOW_TIME;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT);
    glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH) / 2) - (Window::WINDOW_WIDTH / 2), (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (Window::WINDOW_HEIGHT / 2));
    glutCreateWindow("Assn3-1");
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboardDown);
    glutSpecialFunc(specialKeyboardDown);
    glutSpecialUpFunc(specialKeyboardUp);
    glutIdleFunc(updateFrame);

    // gameplay.startGame();
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glutMainLoop();

    return 0;
}