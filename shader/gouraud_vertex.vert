#version 400

layout (location = 0) in vec3 modelPos;
layout (location = 1) in vec3 modelNormalVec;

#define MAX_POINT_LIGHT 16

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

out vec3 fragPos;
out vec3 fragNormalVec;
out vec4 resultColor;

vec4 getDirectionalLight(DirectionalLightFactors factors, vec3 normal, vec3 viewPos) {
    vec3 ambient, diffuse, specular;
    
    // Ambient
    ambient = factors.ambientStrength * vec3(factors.color);

    // Diffuse
    vec3 lightDirection = normalize(-factors.lightDirection);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * vec3(factors.color);

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    specular = specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess) * vec3(lightColor);

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
    vec3 lightDirection = normalize(-factors.lightDirection);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * vec3(factors.color) * attenuation;

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    specular = specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess) * vec3(lightColor) * attenuation;

    return vec4(ambient + diffues + specular , factors.color.w);
}


void main() {
    gl_Position = mvp * vec4(modelPos, 1.0f);
    vec3 fragPos = vec3(modelViewMat * vec4(modelPos, 1.0f));
    vec3 fragNormalVec = modelViewMatForNormal * modelNormalVec;

    vec3 normal = normalize(fragNormalVec);
    
    vec4 directionalLighting = getDirectionalLight(dFactors, normal, viewPos);
    vec4 pointLighting(0.0f);
    for (int i = 0; i < pointLightNumber; i++)
        pointLighting += getPointLight(pFactors[i], fragPos, normal, viewPos);

    resultColor = (directionalLighting + pointLighting) * objColor;
}