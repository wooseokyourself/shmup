#ifndef __GAMEPLAY__
#define __GAMEPLAY__

#include <queue>
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
    void allPass ();
    void allFail ();

private:
    void spotEnemy ();
    void checkHit (Airplane* attacker, Airplane* target);
    void handleMovement (const bool* keyBuffer);

private: // Objects
    Airplane* player;
    Airplane* enemy;

private:
    uint8_t MAX_STAGE;
    uint8_t stage;
};


#endif