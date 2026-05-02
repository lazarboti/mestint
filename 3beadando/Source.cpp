#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

enum eVertexArrayObject {
    VAOVerticesData,
    VAOCount
};
enum eBufferObject {
    VBOVerticesData,
    BOCount
};
enum eProgram {
    QuadScreenProgram,
    ProgramCount
};
enum eTexture {
    NoTexture,
    TextureCount
};

#include "common.cpp"

GLchar windowTitle[] = "Hazi Feladat 3 - Kamera es Feny";

float kameraSzog = 0.0f;
float kameraMagassag = 0.0f;
float kameraSugar = 8.0f;
bool fenyBe = true;

GLuint alakzatVao[2], alakzatVbo[2];
GLuint progID;
GLuint modellLoc, nezetLoc, vetitesLoc, fenyPozLoc, napELoc, fenyBeLoc;
GLuint texturaID;

int gombPontokSzama = 0;

void framebufferSizeCallback(GLFWwindow* w, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

void cursorPosCallback(GLFWwindow* w, double x, double y) {}

void mouseButtonCallback(GLFWwindow* w, int gomb, int akcio, int mods) {}

void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(w, GLFW_TRUE);

    if (action == GLFW_PRESS) keyboard[key] = GL_TRUE;
    else if (action == GLFW_RELEASE) keyboard[key] = GL_FALSE;

    if (key == GLFW_KEY_L && action == GLFW_PRESS) {
        fenyBe = !fenyBe;
    }
}

void initGeometria() {
    float kockaAdatok[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f
    };

    glBindVertexArray(alakzatVao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, alakzatVbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kockaAdatok), kockaAdatok, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    vector<float> gombAdatok;
    int szelet = 30;
    float gombSugar = 0.25f;
    for (int i = 0; i < szelet; i++) {
        float lat1 = (M_PI / szelet) * i - M_PI / 2;
        float lat2 = (M_PI / szelet) * (i + 1) - M_PI / 2;
        for (int j = 0; j < szelet; j++) {
            float lon1 = (2 * M_PI / szelet) * j;
            float lon2 = (2 * M_PI / szelet) * (j + 1);

            float x1 = cos(lat1) * cos(lon1); float y1 = cos(lat1) * sin(lon1); float z1 = sin(lat1);
            float x2 = cos(lat1) * cos(lon2); float y2 = cos(lat1) * sin(lon2); float z2 = sin(lat1);
            float x3 = cos(lat2) * cos(lon1); float y3 = cos(lat2) * sin(lon1); float z3 = sin(lat2);
            float x4 = cos(lat2) * cos(lon2); float y4 = cos(lat2) * sin(lon2); float z4 = sin(lat2);

            float u1 = (float)j / szelet; float v1 = (float)i / szelet;
            float u2 = (float)(j + 1) / szelet; float v2 = (float)i / szelet;
            float u3 = (float)j / szelet; float v3 = (float)(i + 1) / szelet;
            float u4 = (float)(j + 1) / szelet; float v4 = (float)(i + 1) / szelet;

            gombAdatok.insert(gombAdatok.end(), {x1 * gombSugar, y1 * gombSugar, z1 * gombSugar, x1, y1, z1, u1, v1});
            gombAdatok.insert(gombAdatok.end(), {x2 * gombSugar, y2 * gombSugar, z2 * gombSugar, x2, y2, z2, u2, v2});
            gombAdatok.insert(gombAdatok.end(), {x3 * gombSugar, y3 * gombSugar, z3 * gombSugar, x3, y3, z3, u3, v3});

            gombAdatok.insert(gombAdatok.end(), {x2 * gombSugar, y2 * gombSugar, z2 * gombSugar, x2, y2, z2, u2, v2});
            gombAdatok.insert(gombAdatok.end(), {x4 * gombSugar, y4 * gombSugar, z4 * gombSugar, x4, y4, z4, u4, v4});
            gombAdatok.insert(gombAdatok.end(), {x3 * gombSugar, y3 * gombSugar, z3 * gombSugar, x3, y3, z3, u3, v3});
        }
    }
    gombPontokSzama = gombAdatok.size() / 8;

    glBindVertexArray(alakzatVao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, alakzatVbo[1]);
    glBufferData(GL_ARRAY_BUFFER, gombAdatok.size() * sizeof(float), gombAdatok.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void initTextura() {
    glGenTextures(1, &texturaID);
    glBindTexture(GL_TEXTURE_2D, texturaID);
    
    unsigned char texAdat[128][128][3];
    for(int i = 0; i < 128; i++) {
        for(int j = 0; j < 128; j++) {
            texAdat[i][j][0] = 255;
            texAdat[i][j][1] = 160 + (rand() % 95);
            texAdat[i][j][2] = 20;
        }
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, texAdat);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void initAdatok() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    ShaderInfo shader_info[] = {
        { GL_VERTEX_SHADER, "./vertexShader.glsl" },
        { GL_FRAGMENT_SHADER, "./fragmentShader.glsl" },
        { GL_NONE, nullptr }
    };
    progID = LoadShaders(shader_info);
    glUseProgram(progID);

    modellLoc = glGetUniformLocation(progID, "modell");
    nezetLoc = glGetUniformLocation(progID, "nezet");
    vetitesLoc = glGetUniformLocation(progID, "vetites");
    fenyPozLoc = glGetUniformLocation(progID, "fenyPoz");
    napELoc = glGetUniformLocation(progID, "napE");
    fenyBeLoc = glGetUniformLocation(progID, "fenyBe");

    glGenVertexArrays(2, alakzatVao);
    glGenBuffers(2, alakzatVbo);

    initGeometria();
    initTextura();
}

int main(void) {
    init(3, 3, GLFW_OPENGL_COMPAT_PROFILE);
    
    windowWidth = 800;
    windowHeight = 600;
    glfwSetWindowSize(window, windowWidth, windowHeight);
    
    initAdatok();
    
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    while (!glfwWindowShouldClose(window)) {
        if (keyboard[GLFW_KEY_UP]) kameraMagassag += 0.1f;
        if (keyboard[GLFW_KEY_DOWN]) kameraMagassag -= 0.1f;
        if (keyboard[GLFW_KEY_LEFT]) kameraSzog -= 0.03f;
        if (keyboard[GLFW_KEY_RIGHT]) kameraSzog += 0.03f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(progID);

        float camX = kameraSugar * cos(kameraSzog);
        float camY = kameraSugar * sin(kameraSzog);
        float camZ = kameraMagassag;
        
        mat4 nezet = lookAt(vec3(camX, camY, camZ), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
        mat4 vetites = perspective(radians(55.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
        
        glUniformMatrix4fv(nezetLoc, 1, GL_FALSE, value_ptr(nezet));
        glUniformMatrix4fv(vetitesLoc, 1, GL_FALSE, value_ptr(vetites));

        float idozito = glfwGetTime();
        float fenyX = (2.0f * kameraSugar) * cos(idozito);
        float fenyY = (2.0f * kameraSugar) * sin(idozito);
        vec3 aktualisFenyPoz = vec3(fenyX, fenyY, 0.0f);
        
        glUniform3fv(fenyPozLoc, 1, value_ptr(aktualisFenyPoz));
        glUniform1i(fenyBeLoc, fenyBe ? 1 : 0);

        glUniform1i(napELoc, 0);
        glBindVertexArray(alakzatVao[0]);

        mat4 modell1 = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modellLoc, 1, GL_FALSE, value_ptr(modell1));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        mat4 modell2 = translate(mat4(1.0f), vec3(0.0f, 0.0f, 2.0f));
        glUniformMatrix4fv(modellLoc, 1, GL_FALSE, value_ptr(modell2));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        mat4 modell3 = translate(mat4(1.0f), vec3(0.0f, 0.0f, -2.0f));
        glUniformMatrix4fv(modellLoc, 1, GL_FALSE, value_ptr(modell3));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glUniform1i(napELoc, 1);
        glBindVertexArray(alakzatVao[1]);
        glBindTexture(GL_TEXTURE_2D, texturaID);
        
        mat4 napModell = translate(mat4(1.0f), aktualisFenyPoz);
        glUniformMatrix4fv(modellLoc, 1, GL_FALSE, value_ptr(napModell));
        glDrawArrays(GL_TRIANGLES, 0, gombPontokSzama);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanUpScene(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}