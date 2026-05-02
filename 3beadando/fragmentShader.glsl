#version 330 core

in vec3 fragPoz;
in vec3 fragNorm;
in vec2 fragUV;

uniform vec3 fenyPoz;
uniform int napE;
uniform int fenyBe;
uniform sampler2D napTextura;

out vec4 szinKi;

void main() {
    if (napE == 1) {
        vec4 texSzin = texture(napTextura, fragUV);
        szinKi = vec4(texSzin.rgb, 1.0);
    } else {
        vec3 targySzin = vec3(1.0, 1.0, 1.0);
        vec3 fenySzin = vec3(1.0, 0.8, 0.2);
        
        vec3 ambient = 0.1 * targySzin;
        
        if (fenyBe == 1) {
            vec3 norm = normalize(fragNorm);
            vec3 fenyIrany = normalize(fenyPoz - fragPoz);
            float diff = max(dot(norm, fenyIrany), 0.0);
            vec3 diffuse = diff * fenySzin * targySzin;
            
            szinKi = vec4(ambient + diffuse, 1.0);
        } else {
            szinKi = vec4(ambient, 1.0);
        }
    }
}