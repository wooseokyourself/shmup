#version 400

uniform mat4 projection, transform;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
  
void main()
{
    gl_Position = projection * transform * vec4(aPos, 1.0f);
    Normal = aNormal;
}