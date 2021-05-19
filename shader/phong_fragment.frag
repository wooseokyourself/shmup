#version 400

uniform vec4 color;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float ambientStrength;
uniform float specularStrength;
uniform float shininess;

in vec3 fragPos;
in vec3 fragNormalVec;

out vec4 fragColor;

void main()
{
    vec3 ambient, diffuse, specular;
    vec3 norm = normalize(fragNormalVec);

    // Ambient
    ambient = ambientStrength * vec3(lightColor);
    
    // Diffuse
    vec3 lightDirection = normalize(lightPos - fragPos);
    float angle = max(dot(norm, lightDirection), 0.0f);
    diffuse = angle * vec3(lightColor);

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    specular = specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0f), shininess) * vec3(lightColor);

    // fragColor = vec4((ambient + diffuse + specular), 1.0f) * color;
    fragColor = vec4(ambient + diffuse + specular, 1.0f) * color;
} 