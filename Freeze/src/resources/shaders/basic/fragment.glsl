#version 330 core

uniform float resolution;
uniform float time;
in vec4 v2fWpos;
in vec4 v2fPos;
out vec4 fColor;

void main(){

    // fColor =    (v2fWpos  / resolution + 0.1) ;
    fColor = vec4(v2fWpos.x, v2fWpos.y * sin(time * 2.0), v2fWpos.z, 1.0) / resolution + 0.1;
};