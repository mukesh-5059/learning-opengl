#include "utils.hpp"
#include "GLFW/glfw3.h"

#include <iostream>

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

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

    VertexArray va1;
    VertexBuffer vb(pos, 16 * sizeof(float));
    VertexArrayLayout vl;
    vl.push(GL_FLOAT, 2, GL_FALSE);
    vl.push(GL_FLOAT, 2, GL_FALSE);
    va1.bindLayout(vb, vl);
    va1.bind();

    IndexBuffer ibo(indices, 6);

    std::string vertexShader, fragmentShader;
    std::cout << "Loading vertex shader:" << std::endl;
    loadShader("res/shaders/vertex.shader", vertexShader);
    std::cout << "Loading fragment shader:" << std::endl;
    loadShader("res/shaders/fragment.shader", fragmentShader);


    unsigned int prog = createProgram(vertexShader, fragmentShader);
    glUseProgram(prog);

    int location = glGetUniformLocation(prog, "uColor");
    
    float r = 0.0;
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