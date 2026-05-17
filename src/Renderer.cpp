#include <glad/glad.h>
#include "Renderer.hpp"
#include <stdlib.h>
#include <iostream>

Renderer::Renderer(int width, int height, float targetFps)
 : width(width), height(height), targetFps(targetFps){

    targetFrametime = 1.0 / targetFps;
    if (!glfwInit())
        exit(-1);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);  //debugging line
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "iyan window", NULL, NULL);
    if (!window)
    { 
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);


    int version = gladLoadGL();
    if (version == 0) {
        std::cout << "Failed to initialize OpenGL context\n" << std::endl;
        exit(-1);
    }
    std::cout << "\nloaded " << glGetString(GL_VERSION) << std::endl;

    glViewport(0, 0, width, height);
    glClearColor(0.07, 0.13, 0.17, 1.0);

    enableDebugger();  //debugging line
}

void Renderer::clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Renderer::~Renderer(){

}