#ifndef __GAMEPLAY__
#define __GAMEPLAY__

#include <queue>
#include "gameplay/Constants.hpp"
#include "gameplay/Ai.hpp"
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

private: // Objects
    Object* gameworld; // root of scene graph
    Ui* ui;
    Airplane* player;
    Airplane* enemy;
    ThirdObjectManager* playerBulletManager;
    ThirdObjectManager* enemyBulletManager;
    ThirdObjectManager* itemManager;

private: // Objects Attributes for Initializing
    GLfloat airplaneWidth;
    TransformMatrix playerInitMat;
    TransformMatrix enemyInitMat;
    GLfloat playerSpeed;
    GLfloat playerBulletSpeed;
    GLfloat enemySpeed;
    GLfloat enemyBulletSpeed;

private: // Game Play
    uint8_t stage;
    bool allPassMode;
    bool allFailMode;

private: // Enemy AI
    Ai enemyAi;
    int enemyRegenIntervalSecs;
};

#endif