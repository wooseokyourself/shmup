#version 400

#define MAX_POINT_LIGHT 16

// @lightingFlag
#define LIGHTING_ALL 1
#define DIRECTIONAL_LIGHTING_ONLY 2
#define POINT_LIGHTING_ONLY 3
#define NO_LIGHTING 4

layout (location = 0) in vec3 modelPos;
layout (location = 1) in vec3 modelNormalVec;
layout (location = 2) in vec2 modelTextureCoord;
layout (location = 3) in vec3 modelTangent;
layout (location = 4) in vec3 modelBitangent;

struct DirectionalLightFactors {
    vec4 color;
    vec3 lightDirection;
    float ambientStrength;
    float specularStrength;
    float shininess;
};

struct PointLightFactors {
    vec4 color;
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

uniform vec3 directionalLightDir;
uniform vec3 pointLightPos[MAX_POINT_LIGHT];
uniform vec3 viewPos;

uniform sampler2D textureNormal;

uniform DirectionalLightFactors dFactors;
uniform PointLightFactors pFactors[MAX_POINT_LIGHT];
uniform int pointLightNumber;

uniform int lightingFlag;
uniform bool hasTexture;
uniform bool diffuseMapOn;
uniform bool normalMapOn;

in vec3 fragPos;

vec3 fragNormalVec;

vec3 vertOutDirectionalLightDir;
vec3 vertOutPointLightPos[MAX_POINT_LIGHT];
vec3 vertOutViewPos;
vec3 vertOutFragPos;

out vec2 textureCoord;
out vec4 vertOutLighting;

vec3 getDirectionalLight(DirectionalLightFactors factors, vec3 normal) {
    vec3 ambient, diffuse, specular;
    
    // Ambient
    ambient = factors.ambientStrength * factors.color.rgb;

    // Diffuse
    vec3 lightDirection = normalize(vertOutDirectionalLightDir);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * factors.color.rgb;

    // Specular
    vec3 viewDirection = normalize(vertOutViewPos - vertOutFragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    specular = factors.color.rgb * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess);

    return ambient + diffuse + specular;
}

vec3 getPointLight(PointLightFactors factors, vec3 normal, vec3 lightPos) {
    float attenuation;
    vec3 ambient, diffuse, specular;

    // Attenuation
    float distance = length(lightPos - vertOutFragPos);
    attenuation = 1.0 / (factors.constant + factors.linear * distance + factors.quadratic * (distance * distance)); 

    // Ambient
    ambient = factors.ambientStrength * factors.color.rgb * attenuation;

    // Diffuse
    vec3 lightDirection = normalize(lightPos);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * factors.color.rgb * attenuation;

    // Specular
    vec3 viewDirection = normalize(vertOutViewPos - vertOutFragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    specular = factors.color.rgb * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess) * attenuation;

    return ambient + diffuse + specular;
}

void main() {
    gl_Position = mvp * vec4(modelPos, 1.0f);
    vec3 fragPos = vec3(modelViewMat * vec4(modelPos, 1.0f));
    textureCoord = modelTextureCoord;
    vec3 N = modelViewMatForNormal * modelNormalVec; // fragNormalVec
    if (normalMapOn) {
        vec3 _T = normalize(modelViewMatForNormal * modelTangent);
        vec3 T = normalize(_T - dot(_T, N) * N);
        vec3 B = cross(N, T);
        mat3 TBN = transpose(mat3(T, B, N));
        vertOutDirectionalLightDir = TBN * directionalLightDir;
        for (int i = 0; i < pointLightNumber; i++) 
            vertOutPointLightPos[i] = TBN * pointLightPos[i];
        vertOutViewPos = TBN * viewPos;
        vertOutFragPos = TBN * fragPos;
    }
    else {
        fragNormalVec = N;
        vertOutDirectionalLightDir = directionalLightDir;
        for (int i = 0; i < pointLightNumber; i++) 
            vertOutPointLightPos[i] = pointLightPos[i];
        vertOutViewPos = viewPos;
        vertOutFragPos = fragPos;
    }

    vec3 normal = normalMapOn ? normalize(texture(textureNormal, textureCoord).rgb * 2.0f - 1.0f) : fragNormalVec;

    vec3 directionalLighting = getDirectionalLight(dFactors, normal);

    vec3 pointLighting;
    pointLighting.x = 0.0f;
    pointLighting.y = 0.0f;
    pointLighting.z = 0.0f;
    for (int i = 0; i < pointLightNumber; i++)
        pointLighting += getPointLight(pFactors[i], normal, vertOutPointLightPos[i]);

    vec3 resultLighting;

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
        case NO_LIGHTING: default: {
            resultLighting.x = 1.0f;
            resultLighting.y = 1.0f;
            resultLighting.z = 1.0f;
            break;
        }
    }
    vertOutLighting = vec4(resultLighting, 1.0f);
}