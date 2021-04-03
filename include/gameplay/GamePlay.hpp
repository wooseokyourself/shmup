#ifndef __GAMEPLAY__
#define __GAMEPLAY__

#include <queue>
#include "gameplay/Constants.hpp"
#include "gameplay/Ai.hpp"
#include "base/core/Rect.hpp"
#include "base/core/Triangle.hpp"
#include "entity/Airplane.hpp"
#include "entity/ThirdObjectManager.hpp"
#include "entity/Ui.hpp"

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
    Object* gameworld;
    Ui* ui;
    Airplane* player;
    Airplane* enemy;
    ThirdObjectManager* playerBulletManager;
    ThirdObjectManager* enemyBulletManager;
    ThirdObjectManager* itemManager;

private: // Objects Attributes
    GLfloat airplaneWidth;
    TransformMatrix playerInitMat;
    TransformMatrix enemyInitMat;
    GLfloat playerSpeed;
    GLfloat playerBulletSpeed;
    GLfloat enemySpeed;
    GLfloat enemyBulletSpeed;

private:
    uint8_t stage;
    int enemyRegenIntervalSecs;
    bool allPassMode;
    bool allFailMode;
};

#endif