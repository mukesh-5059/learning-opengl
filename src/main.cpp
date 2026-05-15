#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

void enableDebugger();

int main(void)
{
    Renderer renderer(1920, 1080, 60.0);

    float pos[16] = {
          -0.5, -0.5, 0.0, 0.0,
           0.5, -0.5, 1.0, 0.0,
           0.5,  0.5, 1.0, 1.0,
         -0.5, 0.5, 0.0, 1.0
    };

     float vertices[32] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
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

    glm::mat4 baseMat(1.0);
    glm::mat4 proj;
    //glm::mat4 proj = glm::ortho(-1.0, 1.0,
    //                 -0.5625, 0.5625, -1.0, 1.0);
    glm::mat4 trans = glm::translate(baseMat, glm::vec3(0.0f, 0.0f, -2.0f));
    //printMat4(proj);
    Camera camera(renderer);
    

    shader.setInt("u_Texture1", 0);
    shader.setInt("u_Texture2", 1);
    
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(renderer.getWindow(), true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();
    //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    //shader.setMat4f("u_Rotation", trans);
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float lastTime = 0.0, deltaTime = 0.0;
    bool show_another_window = true;
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

        camera.captureInput( deltaTime);
        proj = camera.getProj();
        shader.setMat4f("u_MVP", proj);
        
        //std::cout << deltaTime << std::endl;
        renderer.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

       glm::mat4 rot = glm::rotate(trans, (float)glfwGetTime() , glm::vec3(0.0f, 0.0f, 1.0f));
       glm::mat4 lookAt = camera.getLookAt();
       //glm::mat4 lookAt = glm::translate(baseMat, -camera.getPos());
       shader.setMat4f("u_LookAt", lookAt);
       shader.setMat4f("u_ModelMatrix", rot);
       
       if(show_another_window){
            ImGui::Begin("Frame per sec", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("dt: %.3f ms/frame", deltaTime * 1000);
            ImGui::Text("FPS: %.1f", 1/deltaTime);
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
       }

        ImGui::Begin("Control panel");
        ImGui::Checkbox("Fps", &show_another_window);
        ImGui::End();
       
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, NULL);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(renderer.getWindow());
        glfwPollEvents();
    }

    std::cout << glfwGetTime() << std::endl;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}