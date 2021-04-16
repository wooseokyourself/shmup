#ifndef __GAMEPLAY__
#define __GAMEPLAY__

#include "core/Object.hpp"
#include "Aircraft.hpp"
#include "World.hpp"

std::string PLAYER_MODEL = "assets/models/player.obj";
std::string ENEMY_MODEL = "assets/models/player.obj";

glm::vec3 PLAYER_INIT_POS(0.0f, WORLD_LIMIT_ABS * 0.1f, WORLD_LIMIT_ABS);
glm::vec3 ENEMY_INIT_POS(0.0f, WORLD_LIMIT_ABS * 0.1f, -WORLD_LIMIT_ABS);

class GamePlay {
public:
    GamePlay () {
        root = new Object;
        player = new Aircraft;
        enemy = new Aircraft;
        
        player->loadModel(PLAYER_MODEL);
        player->setColor(0.75f, 0.75f, 0.75f, 1.0f);
        player->setTranslate(PLAYER_INIT_POS);
        player->setRotate(180.0f, 0.0f, 1.0f, 0.0f);
        player->setScale(0.03, 0.03, 0.03);
        player->setSpeed(0.005);
        enemy->loadModel(ENEMY_MODEL);
        enemy->setColor(0.75f, 0.75f, 0.75f, 1.0f);
        enemy->setTranslate(ENEMY_INIT_POS);
        enemy->setRotate(0.0f, 0.0f, 1.0f, 0.0f);
        enemy->setScale(0.03, 0.03, 0.03);

        root->pushChild(player);
        root->pushChild(enemy);
    }

    ~GamePlay () {
        delete enemy;
        delete player; 
        delete root;
    }

    void render () {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(camPos.x, camPos.y, camPos.z, at.x, at.y, at.z, camUp.x, camUp.y, camUp.z);
        drawGrid();
        root->draw();
    }

public: // Events
    void update (const bool* asyncKeyBuf, std::queue<unsigned char>& discreteKeyBuf) {
        handleAsyncKeyInput(asyncKeyBuf);
        handleDiscreteKeyInput(discreteKeyBuf);

        glm::vec3 playerT = player->getTranslate();
        if (tpsMode) {
            camPos = glm::vec3(playerT.x, playerT.y + 0.1f, playerT.z + 0.35f);
            at = glm::vec3(playerT.x, playerT.y, -AXIS_LIMIT_ABS);
            camUp = glm::vec3(0.0f, 1.0f, 0.0f);
        }
        else {
            camPos = glm::vec3(playerT.x, playerT.y, playerT.z);
            at = glm::vec3(playerT.x, playerT.y, -AXIS_LIMIT_ABS);
            camUp = glm::vec3(0.0f, 1.0f, 0.0f);
        }
    }

    void handleAsyncKeyInput (const bool* asyncKeyBuf) {
        const bool* buf = asyncKeyBuf;
        if (buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
            player->move(180.0f); // left
        else if (!buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
            player->move(90.0f); // up
        else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
            player->move(0.0f); // right
        else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
            player->move(270.f); // down
        else if (buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
            player->move(135.0f); 
        else if (!buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
            player->move(45.0f);
        else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
            player->move(315.0f);
        else if (buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
            player->move(225.0f);
    }

    void handleDiscreteKeyInput (std::queue<unsigned char>& discreteKeyBuf) {
        while (!discreteKeyBuf.empty()) {
            unsigned char key = discreteKeyBuf.front();
            discreteKeyBuf.pop();
            switch (key) {
                case ' ':
                    if (!allFailMode)
                        // player->fire(playerBulletManager);
                    break;
                case 'c':
                    if (!allPassMode) {
                        std::cout << "All Pass On" << std::endl;
                        allPassMode = true;
                        allFailMode = false;
                    }
                    else {
                        std::cout << "All Pass Off" << std::endl;
                        allPassMode = false;
                    }
                    break;
                case 'f':
                    if (!allFailMode) {
                        std::cout << "All Fail On" << std::endl;
                        allFailMode = true;
                        allPassMode = false;
                    }
                    else {
                        std::cout << "All Fail Off" << std::endl;
                        allFailMode = false;
                    }
                    break;
                case 'r':
                    if (!renderingMode) {
                        std::cout << "Rendering Mode On" << std::endl;
                        renderingMode = true;
                    }
                    else {
                        std::cout << "Rendering Mode Off" << std::endl;
                        renderingMode = false;
                    }
                    break;
                case 'v':
                    if (!tpsMode) {
                        std::cout << "View Mode: TPS" << std::endl;
                        tpsMode = true;
                    }
                    else {
                        std::cout << "View Mode: FPS" << std::endl;
                        tpsMode = false;
                    }
                    break;
            }
        }
    }

private: // Scene graph
    Object* root;
    Object* player;
    Object* enemy;

private: // Camera
    glm::vec3 camPos;
    glm::vec3 at;
    glm::vec3 camUp;

private: // Variables for game play
    bool allPassMode;
    bool allFailMode;
    bool tpsMode; // 3인칭, 1인칭
    bool renderingMode;
};

#endif