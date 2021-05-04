#version 400

uniform vec4 color;

in vec3 Normal;

out vec4 fragColor;

void main()
{
    fragColor = color;
} 