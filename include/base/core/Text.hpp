#ifndef __TEXT__
#define __TEXT__

#include <string>
#include "base/core/Figure.hpp"

class Text : public Figure {
public:
    Text ();
    void setText (const std::string& _text);

public:
    void draw () const;

private:
    std::string text;
};

#endif