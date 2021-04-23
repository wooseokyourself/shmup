#ifndef __GAMEPLAY__
#define __GAMEPLAY__

#include <iostream>
#include <vector>
#include <queue>

#include "core/Object.hpp"
#include "Constants.hpp"
#include "World.hpp"
#include "Aircraft.hpp"
#include "StraightMovingObjectManager.hpp"
#include "Planetary.hpp"
#include "Ai.hpp"
#include "Hud.hpp"

using namespace std;

class GamePlay {
public:
    GamePlay ();
    ~GamePlay ();
    void start ();
    void renderPerspectiveScene ();
    void renderOrthoScene ();
    void update (const bool* asyncKeyBuf, std::queue<unsigned char>& discreteKeyBuf);

private:
    void handleAsyncKeyInput (const bool* asyncKeyBuf);
    void handleDiscreteKeyInput (std::queue<unsigned char>& discreteKeyBuf);
    void setViewTPS ();
    void setViewFPS ();
    void setView2D ();
    void handleHitNormal (StraightMovingObjectManager* attackerBulletManager, Aircraft* target);
    void handleHitInstantKill (StraightMovingObjectManager* attackerBulletManager, Aircraft* target);
    void handleHitDodge (StraightMovingObjectManager* attackerBulletManager, Aircraft* target);
    void handleGotItem (Aircraft* target);
    void afterPlayerHit ();
    void afterEnemyHit ();

private:
    void win ();
    void lose ();

private: // Perspective
    World* perspectiveSceneRoot;
    Aircraft* player;
    Aircraft* enemy;
    StraightMovingObjectManager* playerBulletManager;
    StraightMovingObjectManager* enemyBulletManager;
    StraightMovingObjectManager* itemManager;
    Planetary* planetaryA;
    Planetary* planetaryB;

private: // Ortho
    Hud* hud;

private: // Camera
    glm::vec3 camPos;
    glm::vec3 at;
    glm::vec3 camUp;

private: // Variables for game play
    Ai enemyAi;
    int stage;
    int gameMode;
    int viewMode; // 3인칭, 1인칭
    bool renderingMode;
};

#endif