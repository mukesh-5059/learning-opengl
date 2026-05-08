#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <iostream>

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

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

    float pos[16] = {
          -0.5, -0.5, -1.0, -1.0,
           0.5, -0.5,  1.0, -1.0,
           0.5,  0.5, 1.0, 1.0,
         -0.5, 0.5,-1.0, 1.0
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va1;
    VertexBuffer vb(pos, 16 * sizeof(float));
    VertexArrayLayout vl;
    vl.add(GL_FLOAT, 2, GL_FALSE);
    vl.add(GL_FLOAT, 2, GL_FALSE);
    va1.bindLayout(vb, vl);
    va1.bind();

    IndexBuffer ibo(indices, 6);

    ShaderProgram shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
    shader.bind();

    int location = shader.getUniformLocation("uColor");
    
    float r = 0.0;
    while (!glfwWindowShouldClose(window) )
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(location, r, 0.1, 0.2, 0.5);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        if(r >=1.0) r = 0.0;
        r += 0.05;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}