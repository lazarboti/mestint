#version 330 core

uniform vec3 szin;
out vec4 outColor;

void main() {
    outColor = vec4(szin, 1.0);
}