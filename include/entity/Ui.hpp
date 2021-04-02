#ifndef __UI__
#define __UI__

#include "base/Object.hpp"
#include "gameplay/Constants.hpp"
#include "entity/Heart.hpp"
#include <string>
#include <vector>

class Ui : public Object {
public:
    Ui ();
    ~Ui ();
    void init (const int playerLives);
    void update (const uint8_t stage, const std::string additionalText, const int playerLives);

public:
    void handlingWhenOutOfBound ();
    void display () const;

private:
    Text* stageText;
    Text* additionalText;
    std::vector<Heart*> lives;
};

#endif