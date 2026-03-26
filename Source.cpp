#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

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

GLchar windowTitle[] = "Hazi Feladat";

float gombX = 0.0f;
float gombY = 0.0f;
float dx = 10.0f / 300.0f;
float dy = 0.0f;
float sugar = 50.0f / 300.0f;

float vonalY = 0.0f;
float vonalFele = 100.0f / 300.0f;

bool szogStart = false;

GLuint myVao[2], myVboP[2], myVboC[2];
GLuint progID;
GLuint eltolasLoc, csereLoc;

void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(w, GLFW_TRUE);

    if (action == GLFW_PRESS) keyboard[key] = GL_TRUE;
    else if (action == GLFW_RELEASE) keyboard[key] = GL_FALSE;

    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        szogStart = true;
        float rad = 25.0f * 3.14159265f / 180.0f;
        float lepes = 10.0f / 300.0f;
        dx = cos(rad) * lepes;
        dy = sin(rad) * lepes;
    }
}

void initAdatok() {
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    ShaderInfo shader_info[] = {
        { GL_VERTEX_SHADER, "./vertexShader.glsl" },
        { GL_FRAGMENT_SHADER, "./fragmentShader.glsl" },
        { GL_NONE, nullptr }
    };
    progID = LoadShaders(shader_info);
    glUseProgram(progID);

    eltolasLoc = glGetUniformLocation(progID, "eltolas");
    csereLoc = glGetUniformLocation(progID, "csere");

    glGenVertexArrays(2, myVao);
    glGenBuffers(2, myVboP);
    glGenBuffers(2, myVboC);

    vector<float> pKord;
    vector<float> pSzin;

    pKord.push_back(0.0f); pKord.push_back(0.0f);
    pSzin.push_back(1.0f); pSzin.push_back(0.0f); pSzin.push_back(0.0f);

    for (int i = 0; i <= 100; i++) {
        float szog = i * 2.0f * 3.14159265f / 100.0f;
        pKord.push_back(cos(szog) * sugar);
        pKord.push_back(sin(szog) * sugar);
        pSzin.push_back(0.0f); pSzin.push_back(1.0f); pSzin.push_back(0.0f);
    }

    glBindVertexArray(myVao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, myVboP[0]);
    glBufferData(GL_ARRAY_BUFFER, pKord.size() * sizeof(float), pKord.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, myVboC[0]);
    glBufferData(GL_ARRAY_BUFFER, pSzin.size() * sizeof(float), pSzin.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    float vonalKord[] = { -vonalFele, 0.0f, vonalFele, 0.0f };
    float vonalSzin[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };

    glBindVertexArray(myVao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, myVboP[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vonalKord), vonalKord, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, myVboC[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vonalSzin), vonalSzin, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glLineWidth(3.0f);
}


void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
}

int main(void) {
    init(3, 3, GLFW_OPENGL_COMPAT_PROFILE);

    windowWidth = 600;
    windowHeight = 600;
    glfwSetWindowSize(window, windowWidth, windowHeight);

    initAdatok();
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window)) {
        gombX += dx;
        if (szogStart) gombY += dy;

        if (gombX + sugar >= 1.0f) {
            gombX = 1.0f - sugar;
            dx = -dx;
        }
        else if (gombX - sugar <= -1.0f) {
            gombX = -1.0f + sugar;
            dx = -dx;
        }

        if (gombY + sugar >= 1.0f) {
            gombY = 1.0f - sugar;
            dy = -dy;
        }
        else if (gombY - sugar <= -1.0f) {
            gombY = -1.0f + sugar;
            dy = -dy;
        }

        if (keyboard[GLFW_KEY_UP] && vonalY < 1.0f) vonalY += 0.02f;
        if (keyboard[GLFW_KEY_DOWN] && vonalY > -1.0f) vonalY -= 0.02f;

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(progID);

        bool xMetsz = (gombX + sugar >= -vonalFele) && (gombX - sugar <= vonalFele);
        bool yMetsz = (gombY - sugar <= vonalY) && (gombY + sugar >= vonalY);

        if (xMetsz && yMetsz) {
            glUniform1i(csereLoc, 0);
        }
        else {
            glUniform1i(csereLoc, 1);
        }

        glBindVertexArray(myVao[0]);
        glUniform2f(eltolasLoc, gombX, gombY);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 102);

        glUniform1i(csereLoc, 0);
        glBindVertexArray(myVao[1]);
        glUniform2f(eltolasLoc, 0.0f, vonalY);
        glDrawArrays(GL_LINES, 0, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanUpScene(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}