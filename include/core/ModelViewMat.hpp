#ifndef __MODELVIEWMAT__
#define __MODELVIEWMAT__

#include <core/glm/glm.hpp>
#include <core/glm/gtc/type_ptr.hpp>
#include <core/glm/gtx/string_cast.hpp>

class ModelViewMat {
public:
    ModelViewMat() {
        translatef = glm::vec3(0.0f, 0.0f, 0.0f);
        scalef = glm::vec3(1.0f, 1.0f, 1.0f);
        mat = glm::mat4(1.0f);
        isUpdated = true;
    }
    void update() { // Translate * Rotate * Scale
        mat = glm::translate(glm::mat4(1.0f), translatef);
        for (int i = rotateAxisStack.size() - 1; i >= 0; i--)
            mat = glm::rotate(mat, glm::radians(angleStack[i]), rotateAxisStack[i]);
        mat = glm::scale(mat, scalef);
        isUpdated = true;
    }
    glm::mat4 get() {
        if (!isUpdated)
            update();
        return mat;
    }
    void translate(const glm::vec3 factors) {
        translatef += factors;
        isUpdated = false;
    }
    void setTranslate(const glm::vec3 factors) {
        translatef = factors;
        isUpdated = false;
    }
    void rotate(const float angle, const glm::vec3 axis) {
        if (angle != 0.0f) {
            rotateAxisStack.push_back(axis);
            angleStack.push_back(angle);
        }
        isUpdated = false;
    }
    void setRotate(const float angle, const glm::vec3 axis) {
        rotateAxisStack.clear();
        angleStack.clear();
        if (angle != 0.0f) {
            rotateAxisStack.push_back(axis);
            angleStack.push_back(angle);
        }
        isUpdated = false;
    }
    void setRotateStack(const std::vector<float> _angleStack, const std::vector<glm::vec3> _rotateAxisStack) {
        angleStack = _angleStack;
        rotateAxisStack = _rotateAxisStack;
        isUpdated = false;
    }
    void setScale(const glm::vec3 factors) {
        scalef = factors;
        isUpdated = false;
    }
    glm::vec3 getTranslate() const {
        return translatef;
    }
    std::vector<float> getAngleStack() const {
        return angleStack;
    }
    std::vector<glm::vec3> getRotateAxisStack() const {
        return rotateAxisStack;
    }
    glm::vec3 getScale() const {
        return scalef;
    }

private:
    glm::mat4 mat;
    glm::vec3 translatef;
    glm::vec3 scalef;
    std::vector<glm::vec3> rotateAxisStack;
    std::vector<float> angleStack;
    bool isUpdated;
};

#endif