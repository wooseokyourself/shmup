#version 400

#define MAX_POINT_LIGHT 16

// @lightingFlag
#define LIGHTING_ALL 1
#define DIRECTIONAL_LIGHTING_ONLY 2
#define POINT_LIGHTING_ONLY 3
#define NO_LIGHTING 4

/*
추후에 LightFactors 에서 strength * color 를 cpu에서 미리 진행하여도 됨.
*/

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

/* // multi texturing
struct Material {
    sampler2D diffuse0;
    sampler2D diffuse1;
    sampler2D diffuse2;
    sampler2D diffuse3;
    sampler2D specular0;
    sampler2D specular1;
    sampler2D specular2;
    sampler2D specular3;
    sampler2D ambient0;
    sampler2D ambient1;
    sampler2D ambient2;
    sampler2D ambient3;
    float shininess;
};
*/

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D ambient;
};

uniform vec4 objColor;
uniform DirectionalLightFactors dFactors;
uniform PointLightFactors pFactors[MAX_POINT_LIGHT];
uniform Material material;
uniform int pointLightNumber;
uniform vec3 viewPos;
uniform int lightingFlag;

in vec3 fragPos;
in vec3 fragNormalVec;
in vec2 textureCoord;

out vec4 fragColor;

vec4 getDirectionalLight(DirectionalLightFactors factors, vec3 normal, vec3 viewPos) {
    vec3 ambient, diffuse, specular;
    
    // Ambient
    ambient = factors.ambientStrength * vec3(factors.color) * texture(material.ambient, textureCoord);

    // Diffuse
    vec3 lightDirection = normalize(factors.lightDirection);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * vec3(factors.color) * texture(material.diffuse, textureCoord);

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    specular = factors.specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess) * vec3(factors.color) * texture(material.specular, textureCoord);

    return vec4(ambient + diffuse + specular, factors.color.w);
}

vec4 getPointLight(PointLightFactors factors, vec3 fragPos, vec3 normal, vec3 viewPos) {
    float attenuation;
    vec3 ambient, diffuse, specular;

    // Attenuation
    float distance = length(factors.lightPosition - fragPos);
    attenuation = 1.0 / (factors.constant + factors.linear * distance + factors.quadratic * (distance * distance)); 

    // Ambient
    ambient = factors.ambientStrength * vec3(factors.color) * texture(material.ambient, textureCoord) * attenuation;

    // Diffuse
    vec3 lightDirection = normalize(factors.lightPosition);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * vec3(factors.color) * texture(material.diffuse, textureCoord) * attenuation;

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    specular = factors.specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess) * vec3(factors.color) * texture(material.specular, textureCoord) * attenuation;

    return vec4(ambient + diffuse + specular, 0.0f);
}

void main() {
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
    fragColor = resultLighting;
}