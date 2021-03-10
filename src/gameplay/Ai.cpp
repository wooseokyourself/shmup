#include "gameplay/Ai.hpp"

void Ai::start (Airplane* _airplane, const int _bulletDirection) {
    airplane = _airplane;
    bulletDirection = _bulletDirection;
    t = std::thread(&Ai::action, this);
}

void Ai::stop () {
    t.join();
}

void Ai::action () {
    while (airplane->isAlive()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 99);
        const int rand = dis(gen);
        const GLfloat lx = airplane->getLeftTop().x;
        const GLfloat rx = airplane->getRightBottom().x;
        int direction = RIGHT;
        if (lx <= -1)
            direction = RIGHT;
        else if (rx >= 1)
            direction = LEFT;
        else {
            if (rand % 10 == 0 || rand % 10 == 9)
                direction = NONE;
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
            airplane->fire();
        std::this_thread::sleep_for(350ms);
    }
}