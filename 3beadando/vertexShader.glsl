#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 uv;

uniform mat4 modell;
uniform mat4 nezet;
uniform mat4 vetites;

out vec3 fragPoz;
out vec3 fragNorm;
out vec2 fragUV;

void main() {
    vec4 vilagPoz = modell * vec4(pos, 1.0);
    fragPoz = vilagPoz.xyz;
    fragNorm = mat3(transpose(inverse(modell))) * norm;
    fragUV = uv;
    gl_Position = vetites * nezet * vilagPoz;
}