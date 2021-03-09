#ifndef __EVENTHANDLER__
#define __EVENTHANDLER__

#include "DynamicObject/Airplane.hpp"

class EventHandler {
public:
    void checkHit (Airplane* attacker, Airplane* target);
};

#endif