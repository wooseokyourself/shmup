#ifndef __TEXT__
#define __TEXT__

#include <string>
#include "base/core/Figure.hpp"

class Text : public Figure {
public:
    Text () : Figure(), text("") { }
    inline void setText (const std::string& _text)  { text = _text; }
    inline std::string getText () const { return text; }

public:
    inline virtual void draw () const {
        glRasterPos2d(0.0f, 0.0f);
        for (int i = 0 ; i < text.size() ; i ++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    }

private:
    std::string text;
};

#endif