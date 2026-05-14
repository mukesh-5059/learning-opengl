#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

void enableDebugger();

int main(void)
{
    Renderer renderer(1920, 1080, 30.0);

    float pos[16] = {
          -0.5, -0.5, 0.0, 0.0,
           0.5, -0.5, 1.0, 0.0,
           0.5,  0.5, 1.0, 1.0,
         -0.5, 0.5, 0.0, 1.0
    };

     float vertices[32] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, -2.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, -2.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, -2.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, -2.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    }; 

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va1;
    VertexBuffer vb(vertices, 4 * 8 * sizeof(float));
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

    IndexBuffer ibo(indices, 6);
    ibo.bind();

    ShaderProgram shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
    shader.bind();

    glm::mat4 trans(1.0);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f),
                     (float)renderer.getWidth()/(float)renderer.getHeight(), 0.1f, 100.0f);
    //glm::mat4 proj = glm::ortho(-1.0, 1.0,
    //                 -0.5625, 0.5625, -1.0, 1.0);
    //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    //printMat4(proj);
    

    shader.setInt("u_Texture1", 0);
    shader.setInt("u_Texture2", 1);
    shader.setMat4f("u_MVP", proj);

    //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    shader.setMat4f("u_Rotation", trans);
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //float r = 0.0;
    float lastTime = 0.0, deltaTime = 0.0;
    while (!glfwWindowShouldClose(renderer.getWindow()) )
    {
        float currentTime = glfwGetTime();

        if (glfwGetKey(renderer.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(renderer.getWindow(), true);

        if(currentTime - lastTime < renderer.getTargetTime()){
            glfwPollEvents();
            continue;
        }
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;


        renderer.clear();
       // shader.setVec4f(r, 0.0, 0.0, 1.0);
       glm::mat4 rot = glm::rotate(trans, (float)glfwGetTime() , glm::vec3(1.0f, 0.0f, 0.0f));
       shader.setMat4f("u_Rotation", rot);
        
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, NULL);
        //if(r >=1.0) r = 0.0;
        //r += 0.05;
        glfwSwapBuffers(renderer.getWindow());
        glfwPollEvents();
    }

    std::cout << glfwGetTime() << std::endl;
    glfwTerminate();
    return 0;
}