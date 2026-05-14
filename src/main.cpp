#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

void enableDebugger();

int main(void)
{
    Renderer renderer(1920, 1080);

    float pos[16] = {
          -0.5, -0.5, 0.0, 0.0,
           0.5, -0.5, 1.0, 0.0,
           0.5,  0.5, 1.0, 1.0,
         -0.5, 0.5, 0.0, 1.0
    };

    float vertices[24] = {
    // positions                         // colors
      0.5f,  -0.5f,  0.0f,   1.0f,  0.0f,  0.0f, 0.0,  0.0,   // bottom right
     -0.5f,  -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,1.0, 0.0,  // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,0.5, 1.0   // top 
    }; 

    unsigned int indices[] = {
        0, 1, 2
       // 2, 3, 0
    };

    VertexArray va1;
    VertexBuffer vb(vertices, 3 * 8 * sizeof(float));
    VertexArrayLayout vl;
    vl.add(GL_FLOAT, 3, GL_FALSE);
    vl.add(GL_FLOAT, 3, GL_FALSE);
    vl.add(GL_FLOAT, 2, GL_FALSE);
    va1.bindLayout(vb, vl);
    va1.bind();

    Texture texture1("res/textures/wall.jpg");
    Texture texture2("res/textures/logo.png");
    
    texture2.bind(1);
    texture1.bind();

    IndexBuffer ibo(indices, 3);
    ibo.bind();

    ShaderProgram shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
    shader.bind();

    shader.setInt("u_Texture1", 0);
    shader.setInt("u_Texture2", 1);
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //float r = 0.0;
    while (!glfwWindowShouldClose(renderer.getWindow()) )
    {
        renderer.clear();

       // shader.setVec4f(r, 0.0, 0.0, 1.0);
        
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, NULL);
        //if(r >=1.0) r = 0.0;
        //r += 0.05;

        glfwSwapBuffers(renderer.getWindow());

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}