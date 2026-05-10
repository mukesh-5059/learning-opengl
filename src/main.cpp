#include <glad/glad.h>
#include "GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "StbImage.h"

#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

void enableDebugger();

int main(void)
{
    Renderer renderer(640, 480);

    float pos[16] = {
          -0.5, -0.5, -1.0, -1.0,
           0.5, -0.5,  1.0, -1.0,
           0.5,  0.5, 1.0, 1.0,
         -0.5, 0.5,-1.0, 1.0
    };

    float vertices[18] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    }; 

    unsigned int indices[] = {
        0, 1, 2
    };

    VertexArray va1;
    VertexBuffer vb(vertices, 18 * sizeof(float));
    VertexArrayLayout vl;
    vl.add(GL_FLOAT, 3, GL_FALSE);
    vl.add(GL_FLOAT, 3, GL_FALSE);
    va1.bindLayout(vb, vl);
    va1.bind();

    IndexBuffer ibo(indices, 3);
    ibo.bind();

    ShaderProgram shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
    shader.bind();

    
    
    float r = 0.0;
    while (!glfwWindowShouldClose(renderer.getWindow()) )
    {
        renderer.clear();

       // shader.setVec4f(r, 0.0, 0.0, 1.0);
        
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, NULL);
        if(r >=1.0) r = 0.0;
        r += 0.05;

        glfwSwapBuffers(renderer.getWindow());

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}