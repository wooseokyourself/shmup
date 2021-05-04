#version 320

layout (location = 0) in vec3 aPos;
uniform mat4 projection, transform;
  
void main()
{
    gl_Position = projection * ransform * vec4(aPos, 1.0f);
}