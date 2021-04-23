
#ifndef __PLANETARY__
#define __PLANETARY__

#include "core/Object.hpp"

class Planetary : public Object {
public:
    Planetary (const std::string aModelPath, const std::string bModelPath, const std::string cModelPath);
    ~Planetary ();
    virtual void update ();
    void init (const glm::vec3 pos, const float maxSize);


private:
    Object* a;
    Object* b;
    Object* c;
    float aAngle;
    float bAngle;
    glm::vec3 aRotateAxis;
    glm::vec3 bRotateAxis;
};

#endif