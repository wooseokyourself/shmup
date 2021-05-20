#version 400

layout (location = 0) in vec3 modelPos;
layout (location = 1) in vec3 modelNormalVec;

#define MAX_POINT_LIGHT 16

// @lightingFlag
#define LIGHTING_ALL 1
#define DIRECTIONAL_LIGHTING_ONLY 2
#define POINT_LIGHTING_ONLY 3
#define NO_LIGHTING 4

struct DirectionalLightFactors {
    vec4 color;
    vec3 lightDirection;
    float ambientStrength;
    float specularStrength;
    float shininess;
};

struct PointLightFactors {
    vec4 color;
    vec3 lightPosition;
    float ambientStrength;
    float specularStrength;
    float shininess;
    float constant;
    float linear;
    float quadratic;
};

uniform mat4 mvp;
uniform mat4 modelViewMat;
uniform mat3 modelViewMatForNormal;

// Lighting
uniform vec4 objColor;
uniform DirectionalLightFactors dFactors;
uniform PointLightFactors pFactors[MAX_POINT_LIGHT];
uniform int pointLightNumber;
uniform vec3 viewPos;
uniform bool directionalLightOn;
uniform int lightingFlag;

out vec3 fragPos;
out vec3 fragNormalVec;
out vec4 resultColor;

vec4 getDirectionalLight(DirectionalLightFactors factors, vec3 normal, vec3 viewPos) {
    vec3 ambient, diffuse, specular;
    
    // Ambient
    ambient = factors.ambientStrength * vec3(factors.color);

    // Diffuse
    vec3 lightDirection = normalize(factors.lightDirection);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * vec3(factors.color);

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    specular = factors.specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess) * vec3(factors.color);

    return vec4(ambient + diffuse + specular, factors.color.w);
}

vec4 getPointLight(PointLightFactors factors, vec3 fragPos, vec3 normal, vec3 viewPos) {
    float attenuation;
    vec3 ambient, diffuse, specular;

    // Attenuation
    float distance = length(factors.lightPosition - fragPos);
    attenuation = 1.0 / (factors.constant + factors.linear * distance + factors.quadratic * (distance * distance)); 

    // Ambient
    ambient = factors.ambientStrength * vec3(factors.color) * attenuation;

    // Diffuse
    vec3 lightDirection = normalize(factors.lightPosition);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * vec3(factors.color) * attenuation;

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    specular = factors.specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess) * vec3(factors.color) * attenuation;

    return vec4(ambient + diffuse + specular, 0.0f);
}


void main() {
    gl_Position = mvp * vec4(modelPos, 1.0f);
    vec3 fragPos = vec3(modelViewMat * vec4(modelPos, 1.0f));
    vec3 fragNormalVec = modelViewMatForNormal * modelNormalVec;

    vec3 normal = normalize(fragNormalVec);
    
    vec4 directionalLighting = getDirectionalLight(dFactors, normal, viewPos);
    vec4 pointLighting;
    pointLighting.x = 0.0f;
    pointLighting.y = 0.0f;
    pointLighting.z = 0.0f;
    pointLighting.w = 1.0f;
    for (int i = 0; i < pointLightNumber; i++)
        pointLighting += getPointLight(pFactors[i], fragPos, normal, viewPos);

    vec4 resultLighting;
    resultLighting.x = 1.0f;
    resultLighting.y = 1.0f;
    resultLighting.z = 1.0f;
    switch (lightingFlag) {
        case LIGHTING_ALL:
            resultLighting = directionalLighting + pointLighting;
            break;
        case DIRECTIONAL_LIGHTING_ONLY:
            resultLighting = directionalLighting;
            break;
        case POINT_LIGHTING_ONLY:
            resultLighting = pointLighting;
            break;
        case NO_LIGHTING: default: 
            break;
    }
    resultColor = resultLighting * objColor;
}