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

out vec3 fragPos;
out vec2 textureCoord;

out vec3 tangentDirectionalLightDir;
out vec3 tangentPointLightPos[MAX_POINT_LIGHT];
out vec3 tangentViewPos;
out vec3 tangentFragPos;

void main() {
    gl_Position = mvp * vec4(modelPos, 1.0f);
    fragPos = vec3(modelViewMat * vec4(modelPos, 1.0f));
    textureCoord = modelTextureCoord;

    vec3 N = modelViewMatForNormal * modelNormalVec; // fragNormalVec
    vec3 _T = normalize(modelViewMatForNormal * modelTangent);
    vec3 T = normalize(_T - dot(_T, N) * N);
    vec3 B = cross(N, T);
    mat3 TBN = transpose(mat3(T, B, N));
    tangentDirectionalLightDir = TBN * directionalLightDir;
    for (int i = 0; i < pointLightNumber; i++) 
        tangentPointLightPos[i] = TBN * pointLightPos[i];
    tangentViewPos = TBN * viewPos;
    tangentFragPos = TBN * fragPos;
}