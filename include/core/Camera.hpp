#ifndef __CAMERA__
#define __CAMERA__

#include <core/glm/glm.hpp>
#include <core/glm/gtc/matrix_transform.hpp>

class Camera {
public:
    void setEyeVec (const glm::vec3& vec) {
        eye = vec;
    }
    void setAtVec (const glm::vec3& vec) {
        at = vec;
    }
    void setUpVec (const glm::vec3& vec) {
        up = vec;
    }
    glm::mat4x4 getMat () const {
        return glm::lookAt(eye, at, up);
    }

public:
    glm::vec3 eye;
    glm::vec3 at;
    glm::vec3 up;
};

#endif