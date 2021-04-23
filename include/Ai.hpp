#ifndef __AI__
#define __AI__

#include "Aircraft.hpp"
#include "StraightMovingObjectManager.hpp"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

class Ai {
public:
    void start (Aircraft* _aircraft, 
                StraightMovingObjectManager* _bulletManager, 
                const float _bulletSize, 
                const glm::vec4 _bulletColor, 
                const float _bulletSpeed);
    void stop ();

private:
    void action ();
    void fire (const int rand);

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