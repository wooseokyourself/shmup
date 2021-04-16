#ifndef __AIRCRAFT__
#define __AIRCRAFT__

#include "core/Object.hpp"

class Aircraft : public Object {
public:
    Aircraft () : Object() { }
    
    virtual void update () {
        Object::update();
    }
    virtual void draw () {
        Object::draw();
    }

public:
    void fire () {
        
    }

};

#endif