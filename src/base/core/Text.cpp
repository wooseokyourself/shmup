#include "base/core/Text.hpp"

Text::Text ()
: Figure(), text("") { }

void Text::setText (const std::string& _text) {
    text = _text;
}

void Text::draw () const {
    glTranslatef(mat.tx, mat.ty, mat.tz);
    glRotatef(mat.degree, 0.0f, 0.0f, 1.0f);

    glColor4f(color.R, color.G, color.B, color.A);
    glRasterPos2d(0.0f, 0.0f);
    for (int i = 0 ; i < text.size() ; i ++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
}