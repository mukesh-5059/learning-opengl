#pragma once
#include "GLFW/glfw3.h"

void enableDebugger();

class Renderer{
    GLFWwindow* window;
    int version;

    public:
    Renderer(int widht, int height);
    void init();
    void clear();
    void draw();
    GLFWwindow* getWindow();

    ~Renderer();
};