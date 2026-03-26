#version 330 core

in vec3 vSzin;
uniform int csere;
out vec4 outColor;

void main() {
    if (csere == 1) {
        outColor = vec4(vSzin.g, vSzin.r, vSzin.b, 1.0);
    } else {
        outColor = vec4(vSzin, 1.0);
    }
}