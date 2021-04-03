#ifndef __AI__
#define __AI__

#include "base/core/Utility.hpp"
#include "entity/Airplane.hpp"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

class Ai {
public:
    void start (Airplane* _airplane, ThirdObjectManager* _bulletManager);
    void stop ();

protected:
    void action ();

private:
    void fire (const int rand);

private:
    Airplane* airplane;
    ThirdObjectManager* bulletManager;

private:
    std::thread t;
};

#endif