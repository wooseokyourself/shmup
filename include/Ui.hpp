#ifndef __UI__
#define __UI__

#include "core/Object.hpp"

class Ui : public Object {
public:
    Ui (const int playerLives);
    void init ();
    void setValue (const uint8_t stage, const std::string additional, const int playerLives);

private:
    std::string stageText;
    std::string additionalText;
    std::vector<Object*> heartPtrs;
};

#endif