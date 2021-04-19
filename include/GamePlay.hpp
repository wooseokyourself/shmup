#ifndef __GAMEPLAY__
#define __GAMEPLAY__

#include "core/Object.hpp"
#include "Constants.hpp"
#include "World.hpp"
#include "Aircraft.hpp"
#include "StraightMovingObjectManager.hpp"
#include "Planetary.hpp"
#include "Ai.hpp"

using namespace std;

namespace AircraftSpeed {
    const float FAST = 0.015;
    const float NORMAL = 0.010;
    const float SLOW = 0.005;
};

namespace BulletSpeed {
    const float FAST = 0.05;
    const float NORMAL = 0.03;
    const float SLOW = 0.01;
};

const int PLAYER_LIVES = 5;
const int MAX_STAGE = 5;

class GamePlay {
public:
    GamePlay () : viewMode(0) {
        stage = 1;
        allPassMode = false;
        allFailMode = false;
        viewMode = VIEWMODE_TPS;
        renderingMode = false;

        root = new Object;
        player = new Aircraft;
        enemy = new Aircraft;
        playerBulletManager = new StraightMovingObjectManager(100, BULLET_MODEL, glm::vec3(0.0f, 0.0f, 1.0f));
        enemyBulletManager = new StraightMovingObjectManager(100, BULLET_MODEL, glm::vec3(0.0f, 0.0f, 1.0f));
        itemManager = new StraightMovingObjectManager(10, ITEM_MODEL, glm::vec3(0.0f, 0.0f, 1.0f));
        planetaryA = new Planetary("assets/models/sphere.obj", "assets/models/sphere.obj", "assets/models/sphere.obj");
        planetaryB = new Planetary("assets/models/earth.obj", "assets/models/moon.obj", "assets/models/satellite.obj");

        player->loadModel(PLAYER_MODEL);
        enemy->loadModel(ENEMY_MODEL);
    
        root->pushChild(planetaryA);
        root->pushChild(planetaryB);
        root->pushChild(player);
        root->pushChild(enemy);
        root->pushChild(playerBulletManager);
        root->pushChild(enemyBulletManager);
        root->pushChild(itemManager);

        cout << "planetaryA: " << planetaryA << endl;
        cout << "planetaryB: " << planetaryB << endl;
        cout << "player: " << player << endl;
        cout << "enemy: " << enemy << endl;
        cout << "playerBulletManager" << playerBulletManager << endl;
        cout << "enemyBulletManager" << enemyBulletManager << endl;
        cout << "itemManager" << itemManager << endl;
    }

    ~GamePlay () {
        delete enemy;
        delete player; 
        delete root;
    }

    void start () {
        planetaryA->init(PLANETARY_A_POS, PLANETARY_A_MAX_SIZE);
        planetaryB->init(PLANETARY_B_POS, PLANETARY_B_MAX_SIZE);
        player->init(PLAYER_INIT_POS, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f), PLAYER_COLOR, PLAYER_MAX_SIZE, AircraftSpeed::FAST, PLAYER_LIVES);
        enemy->init(ENEMY_INIT_POS, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), ENEMY_COLOR, ENEMY_MAX_SIZE, AircraftSpeed::NORMAL, 1);
        enemyAi.start(enemy, enemyBulletManager, ENEMY_BULLET_MAX_SIZE, ENEMY_BULLET_COLOR, BulletSpeed::NORMAL);
    }

    void render () {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(camPos.x, camPos.y, camPos.z, at.x, at.y, at.z, camUp.x, camUp.y, camUp.z);
        drawWorld();
        root->draw();
    }

    void update (const bool* asyncKeyBuf, std::queue<unsigned char>& discreteKeyBuf) {
        // Keyboard input handling
        handleAsyncKeyInput(asyncKeyBuf);
        handleDiscreteKeyInput(discreteKeyBuf);
        if (viewMode == VIEWMODE_2D)  {
            camPos = glm::vec3(0.0f, WORLD_LIMIT_ABS * 2.0f, 0.0f);
            at = glm::vec3(0.0f, 0.0f, 0.0f);
            camUp = glm::vec3(0.0f, 0.0f, -1.0f);
            player->setDraw(true);
        }
        else {
            glm::vec3 playerPos = player->getWorldPos();
            glm::vec3 playerFrontVec = player->getFrontVec();
            glm::vec3 playerUpVec = player->getUpVec();
            if (viewMode == VIEWMODE_TPS) {
                camPos = glm::vec3(playerPos + (-playerFrontVec * 7.0f + playerUpVec * 3.5f));
                player->setDraw(true);
            }
            else if (viewMode == VIEWMODE_FPS) {
                camPos = glm::vec3(playerPos.x, playerPos.y, playerPos.z);
                player->setDraw(false);
            }
            at = playerPos + playerFrontVec;;
            camUp = glm::vec3(playerUpVec);
        }
        

        // Update objects
        root->update();

        // Collision handling
        if (!allPassMode && !allFailMode) {
            handleHitNormal(playerBulletManager, enemy);
            handleHitNormal(enemyBulletManager, player);
        }
        else if (allPassMode && !allFailMode) {
            handleHitInstantKill(playerBulletManager, enemy);
            handleHitDodge(enemyBulletManager, player);
        }
        else if (!allPassMode && allFailMode) {
            handleHitInstantKill(enemyBulletManager, player);
        }
        handleGotItem(player);
        
        // Update gameplay
        if (stage > MAX_STAGE)
            win();
        if (!enemy->isAlive() &&
            (glutGet(GLUT_ELAPSED_TIME) - enemy->getLastDeactivatedTime() >= ENEMY_REGEN_INTERVAL_SECE * 1000)) {
            enemy->init(ENEMY_INIT_POS, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), ENEMY_COLOR, ENEMY_MAX_SIZE, AircraftSpeed::NORMAL, stage);
            for (int i = 1 ; i < enemy->getLives() ; i ++)
                enemy->addShotgunBullet();
            enemyAi.start(enemy, enemyBulletManager, ENEMY_BULLET_MAX_SIZE, ENEMY_BULLET_COLOR, BulletSpeed::NORMAL);
        }
    }

private:
    void handleAsyncKeyInput (const bool* asyncKeyBuf) {
        const bool* buf = asyncKeyBuf;
        if (buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
            player->move(PLAYER_FRAME::LEFT);
        else if (!buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
            player->move(PLAYER_FRAME::FRONT);
        else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
            player->move(-PLAYER_FRAME::LEFT);
        else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
            player->move(-PLAYER_FRAME::FRONT);
        else if (buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
            player->move(PLAYER_FRAME::LEFT + PLAYER_FRAME::FRONT);
        else if (!buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
            player->move(PLAYER_FRAME::FRONT - PLAYER_FRAME::LEFT);
        else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
            player->move(-PLAYER_FRAME::LEFT - PLAYER_FRAME::FRONT);
        else if (buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
            player->move(PLAYER_FRAME::LEFT - PLAYER_FRAME::FRONT);
    }
    void handleDiscreteKeyInput (std::queue<unsigned char>& discreteKeyBuf) {
        while (!discreteKeyBuf.empty()) {
            unsigned char key = discreteKeyBuf.front();
            discreteKeyBuf.pop();
            switch (key) {
                case ' ':
                    if (!allFailMode)
                        player->fire(playerBulletManager, PLAYER_BULLET_MAX_SIZE, PLAYER_BULLET_COLOR, BulletSpeed::FAST);
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
                        root->setRenderingDebug(true);
                    }
                    else {
                        std::cout << "Rendering Mode Off" << std::endl;
                        renderingMode = false;
                        root->setRenderingDebug(false);
                    }
                    break;
                case 'v':
                    if (viewMode == VIEWMODE_2D) {
                        std::cout << "View Mode: TPS" << std::endl;
                        viewMode = VIEWMODE_TPS;
                    }
                    else if (viewMode == VIEWMODE_TPS) {
                        std::cout << "View Mode: FPS" << std::endl;
                        viewMode = VIEWMODE_FPS;
                    }
                    else {
                        std::cout << "View Mode: 2D" << std::endl;
                        viewMode = VIEWMODE_2D;
                    }
                    break;
            }
        }
    }
    void handleHitNormal (StraightMovingObjectManager* attackerBulletManager, Aircraft* target) {
        if (!target->isAlive())
            return;
        if (attackerBulletManager->deactivateObjectWhichIsIn(target)) {
            std::cout << "hit" << std::endl;
            if (target == player)
                afterPlayerHit();
            else
                afterEnemyHit();
        }
    }
    void handleHitInstantKill (StraightMovingObjectManager* attackerBulletManager, Aircraft* target) {
        if (!target->isAlive())
            return;
        if (attackerBulletManager->deactivateObjectWhichIsIn(target)) {
            while (target->isAlive())
                target->loseLife();
            if (target == player)
                afterPlayerHit();
            else
                afterEnemyHit();
        }
    }
    void handleHitDodge (StraightMovingObjectManager* attackerBulletManager, Aircraft* target) {
        if (!target->isAlive())
            return;
        if (attackerBulletManager->deactivateObjectWhichIsIn(target)) { }
    }
    void handleGotItem (Aircraft* target) {
        if (!target->isAlive())
            return;
        if (itemManager->deactivateObjectWhichIsIn(target))
            target->addShotgunBullet();
    }
    void afterPlayerHit () {
        player->loseLife();
        if (!player->isAlive())
            lose();
        player->setRandomColor();
    }
    void afterEnemyHit () {
        std::cout << "enemy hit!" << std::endl;
        enemy->loseLife();
        stage += 1;
        if (!enemy->isAlive()) {
            enemyAi.stop();
            itemManager->activateObject(enemy->getTranslate(), enemy->getAngleStack(), enemy->getRotateAxisStack(), ITEM_MAX_SIZE, ITEM_COLOR, BulletSpeed::SLOW);
        }
    }

private:
    void win () {
        std::cout << "Win!" << std::endl;
        enemyAi.stop();
        glutLeaveMainLoop();
    }
    void lose () {
        std::cout << "Lose.." << std::endl;
        enemyAi.stop();
        glutLeaveMainLoop();
    }

private: // Scene graph
    Object* root;
    Aircraft* player;
    Aircraft* enemy;
    StraightMovingObjectManager* playerBulletManager;
    StraightMovingObjectManager* enemyBulletManager;
    StraightMovingObjectManager* itemManager;
    Planetary* planetaryA;
    Planetary* planetaryB;

private: // Camera
    glm::vec3 camPos;
    glm::vec3 at;
    glm::vec3 camUp;

private: // Variables for game play
    Ai enemyAi;
    int stage;
    bool allPassMode;
    bool allFailMode;
    int viewMode; // 3인칭, 1인칭
    bool renderingMode;
};

#endif