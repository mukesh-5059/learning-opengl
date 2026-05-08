#include "utils.hpp"
#include "GLFW/glfw3.h"
#include <iostream>

void enableDebugger();

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);  //debugging line

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    { 
        glfwTerminate();
        return -1; 
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(5);

    int version = gladLoadGL();
    if (version == 0) {
        std::cout << "Failed to initialize OpenGL context\n" << std::endl;
        return -1;
    }
    std::cout << "\nloaded " << glGetString(GL_VERSION) << std::endl;

    enableDebugger();  //debugging line

    float pos[8] = {
         -0.5, -0.5,
         0.5, -0.5,
         0.5, 0.5,
         -0.5, 0.5
    };
    float pos2[8] = {
         -1.0, -1.0,
          1.0, -1.0,
          1.0, 1.0,
         -1.0, 1.0
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao1;
    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), pos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);

    unsigned int vao2;
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), pos2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


    std::string vertexShader, fragmentShader;
    std::cout << "Loading vertex shader:" << std::endl;
    loadShader("res/shaders/vertex.shader", vertexShader);
    std::cout << "Loading fragment shader:" << std::endl;
    loadShader("res/shaders/fragment.shader", fragmentShader);


    unsigned int prog = createProgram(vertexShader, fragmentShader);
    glUseProgram(prog);

    int location = glad_glGetUniformLocation(prog, "uColor");
    
    float r = 0.0;
    unsigned int arr = vao2; 
    glBindVertexArray(arr);
    while (!glfwWindowShouldClose(window) )
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(location, r, 0.1, 0.2, 0.5);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        if(r >=1.0) r = 0.0;
        r += 0.05;
       // if(arr == vao1) arr = vao2;
       // else arr = vao1;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glDeleteProgram(prog);

    glfwTerminate();
    return 0;
}