#pragma once
#include "GLFW/glfw3.h"

void enableDebugger();

class Renderer{
    GLFWwindow* window;
    int version;
    int width, height;
    float targetFps, targetFrametime;

    public:
    Renderer(int widht, int height, float targetFps);
    void init();
    void clear();
    void draw();

    GLFWwindow* getWindow();
    int getWidth(){return width;}
    int getHeight(){return height;}
    float getTargetTime(){return targetFrametime;}

    ~Renderer();
};