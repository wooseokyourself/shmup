#ifndef __UI__
#define __UI__

#include "base/Object.hpp"
#include "gameplay/Constants.hpp"
#include "entity/Heart.hpp"
#include <string>
#include <vector>

class Ui : public Object {
public:
    Ui (const int playerLives);
    void init ();
    void setValue (const uint8_t stage, const std::string additional, const int playerLives);

public:
    virtual void handlingWhenOutOfBound () { }

private:
    Object* stageText; // Text
    Object* additionalText; // Text
    std::vector<Object*> heartPtrs; // Heart
};

#endif