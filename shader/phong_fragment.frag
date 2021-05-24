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

uniform sampler2D textureDiffuse;

uniform vec4 objColor;
uniform DirectionalLightFactors dFactors;
uniform PointLightFactors pFactors[MAX_POINT_LIGHT];
uniform int pointLightNumber;
uniform vec3 viewPos;
uniform int lightingFlag;
uniform bool textureFlag;

in vec3 fragPos;
in vec3 fragNormalVec;
in vec2 textureCoord;

out vec4 fragColor;

vec3 getDirectionalLight(DirectionalLightFactors factors, vec3 normal, vec3 viewPos) {
    vec3 ambient, diffuse, specular;
    
    // Ambient
    ambient = factors.ambientStrength * factors.color.rgb;

    // Diffuse
    vec3 lightDirection = normalize(factors.lightDirection);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * factors.color.rgb;

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    specular = factors.color.rgb * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess);

    return ambient + diffuse + specular;
}

vec3 getPointLight(PointLightFactors factors, vec3 fragPos, vec3 normal, vec3 viewPos) {
    float attenuation;
    vec3 ambient, diffuse, specular;

    // Attenuation
    float distance = length(factors.lightPosition - fragPos);
    attenuation = 1.0 / (factors.constant + factors.linear * distance + factors.quadratic * (distance * distance)); 

    // Ambient
    ambient = factors.ambientStrength * factors.color.rgb * attenuation;

    // Diffuse
    vec3 lightDirection = normalize(factors.lightPosition);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * factors.color.rgb * attenuation;

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    specular = factors.color.rgb * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess) * attenuation;

    return ambient + diffuse + specular;
}

void main() {
    vec3 normal = normalize(fragNormalVec);

    vec3 directionalLighting = getDirectionalLight(dFactors, normal, viewPos);

    vec3 pointLighting;
    pointLighting.x = 0.0f;
    pointLighting.y = 0.0f;
    pointLighting.z = 0.0f;
    for (int i = 0; i < pointLightNumber; i++)
        pointLighting += getPointLight(pFactors[i], fragPos, normal, viewPos);

    vec3 resultLighting;
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
    fragColor = vec4(resultLighting, 1.0f) * (textureFlag ? texture(textureDiffuse, textureCoord) : objColor);
}