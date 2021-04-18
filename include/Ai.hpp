#ifndef __AI__
#define __AI__

#include "GamePlay.hpp"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

class Ai {
public:
    void start (Aircraft* _aircraft, StraightMovingObjectManager* _bulletManager, const float _bulletSize, const glm::vec4 _bulletColor, const float _bulletSpeed) {
        aircraft = _aircraft;
        bulletManager = _bulletManager;
        bulletSize = _bulletSize;
        bulletColor = _bulletColor;
        bulletSpeed = _bulletSpeed;
        t = std::thread(&Ai::action, this);
    }
    void stop () {
        if (t.joinable())
            t.detach();
    }

private:
    void action () {
        while (aircraft->isAlive()) {
            const int rand = randomIntegerNumber(0, 99);
            const glm::vec3 p = aircraft->getWorldPos();
            glm::vec3 direction = -PLAYER_FRAME::LEFT;
            if (p.x < -WORLD_LIMIT_ABS * 0.9f)
                direction = PLAYER_FRAME::LEFT;
            else if (p.x > WORLD_LIMIT_ABS * 0.9f)
                direction = -PLAYER_FRAME::LEFT;
            else {
                if (rand % 10 == 0 || rand % 10 == 9)
                    direction = glm::vec3(0.0f, 0.0f, 0.0f);
                else if (rand % 2 == 0)
                    direction = PLAYER_FRAME::LEFT;
            }
            int taskMills = (rand % 10) * 100;
            std::thread _t = std::thread(&Ai::fire, this, rand);
            auto START = std::chrono::steady_clock::now();
            while (aircraft->isAlive()) {
                auto NOW = std::chrono::steady_clock::now();
                auto ELAPSED_TIME = std::chrono::duration_cast<std::chrono::milliseconds>(NOW - START).count();
                if (ELAPSED_TIME > taskMills)
                    break;
                if (direction != glm::vec3(0.0f, 0.0f, 0.0f))
                    aircraft->move(direction);
                std::this_thread::sleep_for(16ms);
            }
            _t.join();
        }
    }
    void fire (const int rand) {
        int taskMills = (rand % 10) * 100;
        auto START = std::chrono::steady_clock::now();
        while (aircraft->isAlive()) {
            auto NOW = std::chrono::steady_clock::now();
            auto ELAPSED_TIME = std::chrono::duration_cast<std::chrono::milliseconds>(NOW - START).count();
            if (ELAPSED_TIME > taskMills)
                break;
            if (rand % 2 == 0)
                aircraft->fire(bulletManager, bulletSize, bulletColor, bulletSpeed);
            std::this_thread::sleep_for(350ms);
        }
    }

private:
    Aircraft* aircraft;
    StraightMovingObjectManager* bulletManager;
    float bulletSize;
    glm::vec4 bulletColor;
    float bulletSpeed;

private:
    std::thread t;
};

#endif