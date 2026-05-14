#pragma once
#include "GLFW/glfw3.h"

void enableDebugger();

class Renderer{
    GLFWwindow* window;
    int version;
    int width, height;

    public:
    Renderer(int widht, int height);
    void init();
    void clear();
    void draw();

    GLFWwindow* getWindow();
    int getWidth(){return width;}
    int getHeight(){return height;}

    ~Renderer();
};