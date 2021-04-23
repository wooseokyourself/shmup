#ifndef __HUD__
#define __HUD__

#include "core/Object.hpp"
#include "Constants.hpp"

class Hud : public Object {
public:
    virtual void draw ();
    void init (const int playerLives);
    void setValue (const uint8_t stage, const int viewMode, bool renderingMode, const int gameMode, const int playerLives);
    void setWireframe (bool flag); // override to Object::setWireframe()

private:
    void drawText ();

private:
    std::string stageText;
    std::string viewModeText;
    std::string renderingModeText;
    std::string gameModeText;
    std::vector<Object*> heartPtrs;
};

#endif