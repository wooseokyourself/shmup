#version 400

#define MAX_POINT_LIGHT 16

struct DirectionalLightFactors {
    vec4 color;
    vec3 lightDirection;
    float ambientStrength;
    float specularStrength;
    float shininess;
};

struct PointLightFactors {
    vec4 color;
    vec3 lightPosition;
    float ambientStrength;
    float specularStrength;
    float shininess;
    float constant;
    float linear;
    float quadratic;
};

uniform vec4 objColor;
uniform DirectionalLightFactors dFactors;
uniform PointLightFactors pFactors[MAX_POINT_LIGHT];
uniform int pointLightNumber;
uniform vec3 viewPos;

in vec3 fragPos;
in vec3 fragNormalVec;

out vec4 fragColor;

vec4 getDirectionalLight(DirectionalLightFactors factors, vec3 normal, vec3 viewPos) {
    vec3 ambient, diffuse, specular;
    
    // Ambient
    ambient = factors.ambientStrength * vec3(factors.color);

    // Diffuse
    vec3 lightDirection = normalize(-factors.lightDirection);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * vec3(factors.color);

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    specular = specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess) * vec3(lightColor);

    return vec4(ambient + diffuse + specular, factors.color.w);
}

vec4 getPointLight(PointLightFactors factors, vec3 fragPos, vec3 normal, vec3 viewPos) {
    float attenuation;
    vec3 ambient, diffuse, specular;

    // Attenuation
    float distance = length(factors.lightPosition - fragPos);
    attenuation = 1.0 / (factors.constant + factors.linear * distance + factors.quadratic * (distance * distance)); 

    // Ambient
    ambient = factors.ambientStrength * vec3(factors.color) * attenuation;

    // Diffuse
    vec3 lightDirection = normalize(-factors.lightDirection);
    float angle = max(dot(normal, lightDirection), 0.0f);
    diffuse = angle * vec3(factors.color) * attenuation;

    // Specular
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    specular = specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0f), factors.shininess) * vec3(lightColor) * attenuation;

    return vec4(ambient + diffues + specular , factors.color.w);
}

void main() {
    vec3 normal = normalize(fragNormalVec);
    vec4 light = getDirectionalLight(dFactors, normal, viewPos) + getPointLight(pFactors, fragPos, normal, viewPos);
    fragColor = light * objColor;
}