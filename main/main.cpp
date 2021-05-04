#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

#include "GamePlay.hpp"

using namespace std;

int lastRenderTime = 0;
bool asyncKeyBuf[256];
std::queue<unsigned char> discreteKeyBuf;

// GamePlay* gameplay;

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // 우측 상단
     0.5f, -0.5f, 0.0f,  // 우측 하단
    -0.5f, -0.5f, 0.0f,  // 좌측 하단
    -0.5f,  0.5f, 0.0f   // 좌측 상단
};
unsigned int indices[] = {  // 0부터 시작한다는 것을 명심하세요!
    0, 1, 3,   // 첫 번째 삼각형
    1, 2, 3    // 두 번째 삼각형
};
Shader* shader;
Object* object;
unsigned int VAO, VBO, EBO;

/** @brief GLUT callback. */
void display () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // gameplay->renderPerspectiveScene();
    // gameplay->renderOrthoScene();
    // glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 1000.0f);

    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1000.0f, 1000.0f);
    glm::mat4 cam = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    object->display(projection, cam, glm::mat4(1.0f));

    glutSwapBuffers();
}

/** @brief GLUT callback. */
void reshape (int width, int height) {

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
    // gameplay->update(asyncKeyBuf, discreteKeyBuf);
    glutPostRedisplay();
    lastRenderTime = NOW_TIME;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH) / 2) - (WINDOW_WIDTH / 2), (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (WINDOW_HEIGHT / 2));
    glutCreateWindow("Assn3-2");

#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
#else
    GLenum err = glewInit();
    std::cout << err << std::endl;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
#endif
    printf("%s\n", glGetString(GL_VERSION));
    printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // gameplay = new GamePlay;
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboardDown);
    glutSpecialFunc(specialKeyboardDown);
    glutSpecialUpFunc(specialKeyboardUp);
    glutIdleFunc(updateFrame);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    object = new Object;
    std::string p;
    std::cout << "model: " << std::endl;
    std::cin >> p;
    object->loadModel("assets/models/" + p);
    object->loadShader("shader/vertex.vert", "shader/fragment.frag");
    object->setDraw(true);
    object->setColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    object->setLongestSideTo(0.5f);

    // gameplay->start();
    glutMainLoop();

    return 0;
}