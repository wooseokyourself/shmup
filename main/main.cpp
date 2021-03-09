#include "WorldDefinitions.hpp"
#include "DynamicObject/Airplane.hpp"
#include "EventHandler/EventHandler.hpp"

using namespace std;

Airplane* player = new Airplane(0.0f, -0.5f, 0.3f, 0.1f, 0.05f);
Airplane* enemy = new Airplane(0.0f, 0.5f, 0.3f, 0.1f, 0.05f);
EventHandler eventHandler;
uint8_t stage = 1;

void allpass () {

}

void allfail () {

}

void win () {

}

void lose () {

}

/**
 * @brief GLUT callback
 */
void display () {
    glClear(GL_COLOR_BUFFER_BIT);
    player->display();
    enemy->display();
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
void keyboard (unsigned char key, int x, int y) {
    switch (key) {
        case ' ':
            player->fire();
            break;
        case 'c':
            allpass();
            break;
        case 'f':
            allfail();
            break;
    }
    glutPostRedisplay();
}

/**
 * @brief GLUT callback
 */
void specialkeyboard (int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            player->moveUp();
            break;
        case GLUT_KEY_DOWN:
            player->moveDown();
            break;
        case GLUT_KEY_LEFT:
            player->moveLeft();
            break;
        case GLUT_KEY_RIGHT:
            player->moveRight();
            break;
    }
    glutPostRedisplay();
}

void spotEnemy (int Value) {
    if (enemy->isActivated())
        return;
    enemy->init(++stage);
}

void update () {
    player->update();
    enemy->update();
    eventHandler.checkHit(player, enemy);
    eventHandler.checkHit(enemy, player);
    if (stage > MAX_STAGE)
        win ();
    if (!enemy->isActivated())
        glutTimerFunc(3000, spotEnemy, 1);
}

int main(int argc, char** argv) {
    player->init(3);
    enemy->init(stage);
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
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);
    glutIdleFunc(update);
    glutMainLoop();
    return 0;
}