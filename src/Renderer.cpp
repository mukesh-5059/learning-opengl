#include <glad/glad.h>
#include "Renderer.hpp"
#include <stdlib.h>
#include <iostream>

Renderer::Renderer(int width, int height){
    if (!glfwInit())
        exit(-1);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);  //debugging line

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    { 
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(5);

    int version = gladLoadGL();
    if (version == 0) {
        std::cout << "Failed to initialize OpenGL context\n" << std::endl;
        exit(-1);
    }
    std::cout << "\nloaded " << glGetString(GL_VERSION) << std::endl;

    enableDebugger();  //debugging line
}

void Renderer::clear(){
    glClear(GL_COLOR_BUFFER_BIT);
}

GLFWwindow* Renderer::getWindow(){
    return window;
}

Renderer::~Renderer(){

}