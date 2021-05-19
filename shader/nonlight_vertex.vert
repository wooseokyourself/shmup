#version 400

uniform mat4 mvp;

layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0f);
}