#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

#include "core/Object.hpp"

using namespace std;

int lastRenderTime = 0;

const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 800;

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // ���� ���
     0.5f, -0.5f, 0.0f,  // ���� �ϴ�
    -0.5f, -0.5f, 0.0f,  // ���� �ϴ�
    -0.5f,  0.5f, 0.0f   // ���� ���
};
unsigned int indices[] = {  // 0���� �����Ѵٴ� ���� ����ϼ���!
    0, 1, 3,   // ù ��° �ﰢ��
    1, 2, 3    // �� ��° �ﰢ��
};

Shader* shader;
unsigned int VAO, VBO, EBO;

void reshape(int width, int height) {

}

void updateFrame() {
    const int NOW_TIME = glutGet(GLUT_ELAPSED_TIME);
    glutPostRedisplay();
    lastRenderTime = NOW_TIME;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
    glm::vec3 camPos(0.0f, 5.0f, 0.0f), at(0.0f, 0.0f, 0.0f), up(0.0f, 0.0f, -1.0f);
    glm::mat4 lookAt = glm::lookAt(camPos, at, up);

    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) / 2) - (WINDOW_WIDTH / 2), (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (WINDOW_HEIGHT / 2));
    glutCreateWindow("Assn3-2");


    GLenum err = glewInit();
    std::cout << err << std::endl;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    printf("%s\n", glGetString(GL_VERSION));
    printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glutIgnoreKeyRepeat(1);
    glutIdleFunc(updateFrame);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    // shader ����
    shader = new Shader("shader/vertex.vert", "shader/fragment.frag");
    
    // VAO Ȱ��ȭ
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO ���� (VAO�� ����)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // EBO ���� (VAO�� ����)
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glutMainLoop();

    return 0;
}