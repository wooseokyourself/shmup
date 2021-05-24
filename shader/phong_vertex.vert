#version 400

#define MAX_POINT_LIGHT 16

layout (location = 0) in vec3 modelPos;
layout (location = 1) in vec3 modelNormalVec;
layout (location = 2) in vec2 modelTextureCoord;
layout (location = 3) in vec3 modelTangent;
layout (location = 4) in vec3 modelBitangent;

uniform mat4 mvp;
uniform mat4 modelViewMat;
uniform mat3 modelViewMatForNormal;

uniform vec3 directionalLightDir;
uniform vec3 pointLightPos[MAX_POINT_LIGHT];
uniform vec3 viewPos;
uniform int pointLightNumber;

uniform bool normalMapOn;

out vec3 fragPos;
out vec3 fragNormalVec; // necessary when not using normal mapping
out vec2 textureCoord;

out vec3 vertOutDirectionalLightDir;
out vec3 vertOutPointLightPos[MAX_POINT_LIGHT];
out vec3 vertOutViewPos;
out vec3 vertOutFragPos;

void main() {
    gl_Position = mvp * vec4(modelPos, 1.0f);
    fragPos = vec3(modelViewMat * vec4(modelPos, 1.0f));
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
}