#include "gameplay/Ai.hpp"

/**
 * @brief Let _airplane behave itself.
 * @param _airplane The target airplane. It must be constructed.
 * @param _bulletDirection The bullet direction of the airplane.
 */
void Ai::start (Airplane* _airplane, ThirdObjectManager* _bulletManager) {
    airplane = _airplane;
    bulletManager = _bulletManager;
    t = std::thread(&Ai::action, this);
}

void Ai::stop () {
    if (t.joinable())
        t.detach();
}

void Ai::action () {
    const GLfloat LEFT = 180.0f, RIGHT = 0.0f, STOP = -1.0f;
    while (airplane->isAlive()) {
        const int rand = randomIntegerNumber(0, 99);
        const GLfloat lx = airplane->getHitboxLeftTop().x;
        const GLfloat rx = airplane->getHitboxRightBottom().x;
        GLfloat direction = RIGHT;
        if (lx < WORLD_BOUND::LEFT)
            direction = RIGHT;
        else if (rx > WORLD_BOUND::RIGHT)
            direction = LEFT;
        else {
            if (rand % 10 == 0 || rand % 10 == 9)
                direction = STOP;
            else if (rand % 2 == 0)
                direction = LEFT;
        }
        int taskMills = (rand % 10) * 100;
        std::thread _t = std::thread(&Ai::fire, this, rand);
        auto START = std::chrono::steady_clock::now();
        while (airplane->isAlive()) {
            auto NOW = std::chrono::steady_clock::now();
            auto ELAPSED_TIME = std::chrono::duration_cast<std::chrono::milliseconds>(NOW - START).count();
            if (ELAPSED_TIME > taskMills)
                break;
            if (direction != STOP)
                airplane->move(direction);
            std::this_thread::sleep_for(16ms);
        }
        _t.join();
    }
}

void Ai::fire (const int rand) {
    int taskMills = (rand % 10) * 100;
    auto START = std::chrono::steady_clock::now();
    while (airplane->isAlive()) {
        auto NOW = std::chrono::steady_clock::now();
        auto ELAPSED_TIME = std::chrono::duration_cast<std::chrono::milliseconds>(NOW - START).count();
        if (ELAPSED_TIME > taskMills)
            break;
        if (rand % 2 == 0)
            airplane->fire(bulletManager);
        std::this_thread::sleep_for(350ms);
    }
}