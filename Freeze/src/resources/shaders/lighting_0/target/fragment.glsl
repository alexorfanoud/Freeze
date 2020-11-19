#version 330 core

uniform vec4 objectColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 v2fNormals;
in vec3 v2fPos;
out vec4 fColor;

void main(){
    float ambientStrength = 0.1f;
    vec4 ambient = ambientStrength * lightColor;

    vec3 lightSourceDir = normalize(lightPos - v2fPos);
    vec3 norm = normalize(v2fNormals);
    vec4 diffuse = max(dot(norm, lightSourceDir), 0.0f) * lightColor;
    
    vec3 viewDir = normalize(viewPos - v2fPos);
    vec3 reflectLightDir = reflect(-lightSourceDir, norm);
    vec4 speccular = pow(max(dot(reflectLightDir, viewDir), 0.0f),32.0f) * lightColor;
    

    fColor = (ambient + diffuse + speccular) * objectColor;
}