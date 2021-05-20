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

#endif