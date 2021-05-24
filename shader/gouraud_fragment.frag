#version 400

uniform bool hasTexture;
uniform bool diffuseMapOn;
uniform vec4 objColor;

uniform sampler2D textureDiffuse;

in vec2 textureCoord;
in vec4 vertOutLighting;

out vec4 fragColor;

void main() {
    fragColor = vertOutLighting * (diffuseMapOn && hasTexture ? texture(textureDiffuse, textureCoord) : objColor);
}