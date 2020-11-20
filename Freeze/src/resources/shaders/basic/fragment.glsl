#version 330 core

uniform float resolution;
in vec4 v2fWpos;
out vec4 fColor;

void main(){

    fColor = v2fWpos / resolution;
};