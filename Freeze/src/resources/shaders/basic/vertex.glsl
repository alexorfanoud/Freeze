#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;
out vec4 v2fWpos;
out vec4 v2fPos;
uniform float time;
uniform  mat4 model;
uniform  mat4 view;
uniform  mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(vPos.x, vPos.y * sin(time * 2.0), vPos.z, 1.0f) ;
    v2fWpos = model * vec4(vPos, 1.0f) ;
    v2fPos = vec4(vPos, 1.0f) * 1.0;
};