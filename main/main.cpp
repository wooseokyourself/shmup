#include "gameplay/WorldDefinitions.hpp"
#include "gameplay/GamePlay.hpp"

using namespace std;

static GamePlay handler;
bool asyncKeyBuf[256];
std::queue<unsigned char> discreteKeyBuf;

/**
 * @brief GLUT callback
 */
void display () {
    glClear(GL_COLOR_BUFFER_BIT);
    handler.render();
    glutSwapBuffers();
}

/**
 * @brief GLUT callback
 */
void reshape (int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * @brief GLUT callback
 */
void keyboardDown (unsigned char key, int x, int y) {
    discreteKeyBuf.push(key);
}

/**
 * @brief GLUT callback
 */
void specialKeyboardDown (int key, int x, int y) {
    asyncKeyBuf[key] = true;
}

void specialKeyboardUp (int key, int x, int y) {
    asyncKeyBuf[key] = false;
}

void updateFrame () {
    handler.update(discreteKeyBuf, asyncKeyBuf);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    handler.startGame();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH) / 2) - (WINDOW_WIDTH / 2),
                            (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (WINDOW_HEIGHT / 2));
    glutCreateWindow("Assn1");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboardDown);
    glutSpecialFunc(specialKeyboardDown);
    glutSpecialUpFunc(specialKeyboardUp);
    glutIdleFunc(updateFrame);
    glutMainLoop();
    return 0;
}