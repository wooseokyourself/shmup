#include "gameplay/GamePlay.hpp"

using namespace std;

int lastRenderTime = 0;

static GamePlay gameplay;
bool asyncKeyBuf[256];
std::queue<unsigned char> discreteKeyBuf;

/** @brief GLUT callback. */
void display () {
    glClear(GL_COLOR_BUFFER_BIT);
    gameplay.render();
    glutSwapBuffers();
}

/** @brief GLUT callback. */
void reshape (int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT, 0.0f, 0.0f, 0.0f); // 관측 사각형의 종횡비
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/** @brief GLUT callback. Detect “c”, “f”, and “spaces” keys down. */
void keyboardDown (unsigned char key, int x, int y) {
    discreteKeyBuf.push(key);
}

/** @brief GLUT callback. Detect arrow keys down. */
void specialKeyboardDown (int key, int x, int y) {
    asyncKeyBuf[key] = true;
}

/** @brief GLUT callback. Detect arrow keys up. */
void specialKeyboardUp (int key, int x, int y) {
    asyncKeyBuf[key] = false;
}

/** @brief GLUT callback. */
void updateFrame () {
    const int NOW_TIME = glutGet(GLUT_ELAPSED_TIME);
    if (NOW_TIME - lastRenderTime < TIME_PER_FRAME)
        return;
    gameplay.update(discreteKeyBuf, asyncKeyBuf);
    glutPostRedisplay();
    lastRenderTime = NOW_TIME;
}

int main(int argc, char** argv) {
    gameplay.startGame();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT); // 윈도우의 종횡비
    glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH) / 2) - (Window::WINDOW_WIDTH / 2),
                            (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (Window::WINDOW_HEIGHT / 2));
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