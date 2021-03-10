#ifndef __AI__
#define __AI__

#include "dynamics/Airplane.hpp"
#include <thread>
#include <chrono>
#include <random>
#include <map>

using namespace std::chrono_literals;

class Ai {
public:
    void start (Airplane* _airplane, const int _bulletDirection);
    void stop ();

protected:
    void action ();

private:
    void fire (const int rand);

private:
    Airplane* airplane;
    int bulletDirection;

private:
    std::thread t;
};

#endif