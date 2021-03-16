#ifndef __GAMEPLAY__
#define __GAMEPLAY__

#include <queue>
#include <string>
#include "gameplay/Constants.hpp"
#include "gameplay/Ai.hpp"
#include "dynamics/Airplane.hpp"

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
    void checkHitNormal (Airplane* attacker, Airplane* target);
    void checkHitInstantKill (Airplane* attacker, Airplane* target);
    void checkHitDodge (Airplane* attacker, Airplane* target);

private:
    void handleDiscreteKeyInput (std::queue<unsigned char>& discreteKeyBuf);
    void handleAsyncKeyInput (const bool* asyncKeyBuf);

private:
    Ai enemyAi;

private: // Objects
    Airplane* player;
    Airplane* enemy;

private:
    uint8_t MAX_STAGE;
    uint8_t stage;
    int enemyRegenIntervalSecs;
    bool allPassMode;
    bool allFailMode;
};

#endif