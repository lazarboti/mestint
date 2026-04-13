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

GLchar windowTitle[] = "Bezier Gorbe";

vector<float> pontok;
int fogottPont = -1;
float egerX = 0.0f;
float egerY = 0.0f;

GLuint vao[2], vbo[2];
GLuint progID;
GLuint szinLoc;
int gorbeHossz = 0;

long long kombinacio(int n, int k) {
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;
    long long r = 1;
    for (int i = 1; i <= k; ++i) {
        r = r * (n - i + 1) / i;
    }
    return r;
}

vector<float> szamolGorbe() {
    vector<float> g;
    int n = (pontok.size() / 2) - 1;
    if (n < 0) return g;
    if (n == 0) {
        g.push_back(pontok[0]);
        g.push_back(pontok[1]);
        return g;
    }

    int reszlet = 150;
    for (int j = 0; j <= reszlet; ++j) {
        float t = (float)j / reszlet;
        float px = 0, py = 0;
        for (int i = 0; i <= n; ++i) {
            float suly = kombinacio(n, i) * pow(1.0f - t, n - i) * pow(t, i);
            px += suly * pontok[i * 2];
            py += suly * pontok[i * 2 + 1];
        }
        g.push_back(px);
        g.push_back(py);
    }
    return g;
}

void frissit() {
    if (pontok.size() > 0) {
        glBindVertexArray(vao[0]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, pontok.size() * sizeof(float), pontok.data(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
    }

    vector<float> gorbe = szamolGorbe();
    gorbeHossz = gorbe.size() / 2;

    if (gorbeHossz > 0) {
        glBindVertexArray(vao[1]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, gorbe.size() * sizeof(float), gorbe.data(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
    }
}

void cursorPosCallback(GLFWwindow* w, double x, double y) {
    egerX = (x / windowWidth) * 2.0f - 1.0f;
    egerY = 1.0f - (y / windowHeight) * 2.0f;

    if (fogottPont != -1) {
        pontok[fogottPont * 2] = egerX;
        pontok[fogottPont * 2 + 1] = egerY;
        frissit();
    }
}

void mouseButtonCallback(GLFWwindow* w, int gomb, int akcio, int mods) {
    if (akcio == GLFW_PRESS) {
        int talalt = -1;
        float minTav = 0.05f;
        
        for (size_t i = 0; i < pontok.size() / 2; i++) {
            float dx = pontok[i * 2] - egerX;
            float dy = pontok[i * 2 + 1] - egerY;
            float tav = sqrt(dx * dx + dy * dy);
            if (tav < minTav) {
                talalt = i;
                break;
            }
        }

        if (gomb == GLFW_MOUSE_BUTTON_LEFT) {
            if (talalt != -1) {
                fogottPont = talalt;
            } else {
                pontok.push_back(egerX);
                pontok.push_back(egerY);
                frissit();
            }
        } else if (gomb == GLFW_MOUSE_BUTTON_RIGHT) {
            if (talalt != -1) {
                pontok.erase(pontok.begin() + talalt * 2, pontok.begin() + talalt * 2 + 2);
                frissit();
            }
        }
    } else if (akcio == GLFW_RELEASE) {
        if (gomb == GLFW_MOUSE_BUTTON_LEFT) {
            fogottPont = -1;
        }
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(w, GLFW_TRUE);
}

void initAdatok() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    ShaderInfo shader_info[] = {
        { GL_VERTEX_SHADER, "./vertexShader.glsl" },
        { GL_FRAGMENT_SHADER, "./fragmentShader.glsl" },
        { GL_NONE, nullptr }
    };
    progID = LoadShaders(shader_info);
    glUseProgram(progID);

    szinLoc = glGetUniformLocation(progID, "szin");

    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);

    pontok = {
        -0.8f, -0.5f,
        -0.3f,  0.5f,
         0.3f, -0.5f,
         0.8f,  0.5f
    };

    frissit();

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(9.0f);
    glLineWidth(2.0f);
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
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(progID);

        if (pontok.size() >= 4) {
            glUniform3f(szinLoc, 0.4f, 0.4f, 0.4f);
            glBindVertexArray(vao[0]);
            glDrawArrays(GL_LINE_STRIP, 0, pontok.size() / 2);
        }

        if (gorbeHossz > 0) {
            glUniform3f(szinLoc, 1.0f, 0.8f, 0.0f);
            glBindVertexArray(vao[1]);
            glDrawArrays(GL_LINE_STRIP, 0, gorbeHossz);
        }

        if (pontok.size() > 0) {
            glUniform3f(szinLoc, 0.0f, 0.8f, 1.0f);
            glBindVertexArray(vao[0]);
            glDrawArrays(GL_POINTS, 0, pontok.size() / 2);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanUpScene(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}