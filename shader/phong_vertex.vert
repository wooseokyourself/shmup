#version 400

layout (location = 0) in vec3 modelPos;
layout (location = 1) in vec3 modelNormalVec;

uniform mat4 mvp;
uniform mat4 modelViewMat;
uniform mat3 modelViewMatForNormal;

out vec3 fragPos;
out vec3 fragNormalVec;

void main() {
    gl_Position = mvp * vec4(modelPos, 1.0f);
    fragPos = vec3(modelViewMat * vec4(modelPos, 1.0f));
    fragNormalVec = modelViewMatForNormal * modelNormalVec;
}