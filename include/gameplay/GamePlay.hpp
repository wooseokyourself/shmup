#ifndef __GAMEPLAY__
#define __GAMEPLAY__

#include <queue>
#include <string>
#include "gameplay/Constants.hpp"
#include "gameplay/Ai.hpp"
#include "base/core/Rect.hpp"
#include "base/core/Triangle.hpp"
#include "entity/Airplane.hpp"
#include "entity/ThirdObjectManager.hpp"

class GamePlay {
public:
    GamePlay ();
    ~GamePlay ();

    void startGame ();

    void render ();
    void update (std::queue<unsigned char>& discreteKeyBuf, const bool* asyncKeyBuf);

private:
    void win ();
    void lose ();

private:
    void displayStage ();
    void displayPlayerLives ();
    void displayWall ();

private:
    void handleHitNormal (Airplane* attacker, Airplane* target);
    void handleHitInstantKill (Airplane* attacker, Airplane* target);
    void handleHitDodge (Airplane* attacker, Airplane* target);
    void handleAirplaneGotItem (Airplane* target);

private:
    void handleDiscreteKeyInput (std::queue<unsigned char>& discreteKeyBuf);
    void handleAsyncKeyInput (const bool* asyncKeyBuf);

private:
    Ai enemyAi;

private: // Objects
    GLfloat airplaneWidth;
    Airplane* player;
    Airplane* enemy;
    ModelViewMat2D playerInitMat;
    ModelViewMat2D enemyInitMat;
    GLfloat playerSpeed;
    GLfloat playerBulletSpeed;
    GLfloat enemySpeed;
    GLfloat enemyBulletSpeed;

private:
    ThirdObjectManager itemManager;
    uint8_t MAX_STAGE;
    uint8_t stage;
    int enemyRegenIntervalSecs;
    bool allPassMode;
    bool allFailMode;
};

#endif