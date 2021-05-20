#ifndef __LIGHT__
#define __LIGHT__

#include <core/glm/glm.hpp>
#include <core/glm/gtc/type_ptr.hpp>
#include <core/glm/gtx/string_cast.hpp>

struct DirectionalLightFactors {
    glm::vec4 color;
    glm::vec3 lightDirection;
    float ambientStrength;
    float specularStrength;
    float shininess;
};

struct PointLightFactors {
    glm::vec4 color;
    glm::vec3 lightPosition;
    float ambientStrength;
    float specularStrength;
    float shininess;
    float constant;
    float linear;
    float quadratic;
};

class Light {
public:
    void setColor(const glm::vec4& _color) { color = _color; }
    glm::vec4 getColor() const { return color; }
    void setPos(const glm::vec3& _pos) { pos = _pos; }
    glm::vec3 getPos() const { return pos; }
    void setLightingFactors(const float _ambientStrength, const float _specularStrength, const float _shininess) {
        ambientStrength = _ambientStrength;
        specularStrength = _specularStrength;
        shininess = _shininess;
    }
    
protected:
    glm::vec4 color;
    glm::vec3 pos;
    float ambientStrength;
    float specularStrength;
    float shininess;
};

class DirectionalLight : public Light {
public:
    DirectionalLightFactors getFactors(const glm::vec3& fragmentPos) const {
        DirectionalLightFactors ret;
        ret.color = color;
        ret.lightDirection = pos - fragmentPos;
        ret.ambientStrength = ambientStrength;
        ret.specularStrength = specularStrength;
        ret.shininess = shininess;
        return ret;
    }
};

class PointLight : public Light {
public:
    void setAttenuationFactors(const float _constant, const float _linear, const float _quadratic) {
        constant = _constant;
        linear = _linear;
        quadratic = _quadratic;
    }
    PointLightFactors getFactors() const { 
        PointLightFactors ret;
        ret.color = color;
        ret.lightPosition = pos;
        ret.ambientStrength = ambientStrength;
        ret.specularStrength = specularStrength;
        ret.shininess = shininess;
        ret.constant = constant;
        ret.linear = linear;
        ret. quadratic = quadratic;
    }

private:
    float constant;
    float linear;
    float quadratic;
};

#endif