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

glm::vec3 camPos = glm::vec3(0.0f, 0.3f, WORLD_LIMIT_ABS + 0.35f);
glm::vec3 at = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

Object player("assets/models/player.obj");
Object enemy("assets/models/player.obj");

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

/** @brief GLUT callback. */
void display () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT);
    glLoadIdentity();
    gluLookAt(camPos.x, camPos.y, camPos.z, at.x, at.y, at.z, camUp.x, camUp.y, camUp.z);
    glPushMatrix();
    drawGrid();
    glPopMatrix();

    glColor4f(0.75f, 0.75f, 0.75f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, WORLD_LIMIT_ABS * 0.1f, WORLD_LIMIT_ABS);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glScalef(0.03, 0.03, 0.03);
    player.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, WORLD_LIMIT_ABS * 0.1f, -WORLD_LIMIT_ABS);
    glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
	glScalef(0.03, 0.03, 0.03);
    enemy.draw();
    glPopMatrix();

    glutSwapBuffers();
}

/** @brief GLUT callback. */
void reshape (int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat base = Window::WINDOW_HEIGHT < Window::WINDOW_WIDTH ? Window::WINDOW_HEIGHT : Window::WINDOW_WIDTH;
    GLfloat widthset = Window::WINDOW_WIDTH / base;
    GLfloat heightset = Window::WINDOW_HEIGHT / base;
    gluPerspective(60, Window::WINDOW_WIDTH / Window::WINDOW_HEIGHT, 0.1f, 1000.0f);  
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
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);    
    glDepthFunc(GL_ALWAYS);
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
    

    glutMainLoop();

    return 0;
}