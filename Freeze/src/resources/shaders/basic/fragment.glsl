#version 330 core

in vec4 v2fWpos;
out vec4 fColor;

void main(){

    fColor = v2fWpos * 2.0f;
};