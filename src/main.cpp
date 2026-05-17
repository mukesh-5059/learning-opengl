#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Cube.hpp"

void enableDebugger();

int main(void)
{
    Renderer renderer(1920, 1080, 60.0);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Cube cube;

    Texture texture1("res/textures/wall.jpg");
    Texture texture2("res/textures/face.png");
    
    texture2.bind(1);
    texture1.bind();

    ShaderProgram shader("res/shaders/vertex.vert", "res/shaders/fragment.frag");
    shader.bind();

    glm::mat4 baseMat(1.0);
    glm::mat4 proj;

    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
    

    shader.setInt("u_Texture1", 0);
    shader.setInt("u_Texture2", 1);
    
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(renderer.getWindow(), true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();
    
    float lastTime = 0.0, deltaTime = 0.0;
    bool showFpsWindow = true;
    int n = 10;
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

        camera.captureInput(renderer.getWindow(), deltaTime);
        proj = camera.getProjectionMatrix(renderer.getWidth(), renderer.getHeight());
        shader.setMat4f("u_MVP", proj);
        
        renderer.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

       
       glm::mat4 lookAt = camera.getViewMatrix();
       shader.setMat4f("u_LookAt", lookAt);

       

        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                for(int k = 0; k<n; k++){
                    cube.draw(glm::vec3(i * 2.0f, j * 2.0f, k * -2.0f), (float)glfwGetTime(), shader);
                }
            }
        }
       
       if(showFpsWindow){
            ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
            ImGui::Begin("Frame per sec", &showFpsWindow, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Text("dt: %.3f ms/frame", deltaTime * 1000);
            ImGui::Text("FPS: %.1f", 1/deltaTime);
            ImGui::End();
       }

        ImGui::SetNextWindowPos(ImVec2(10, 80), ImGuiCond_FirstUseEver);
        ImGui::Begin("Control panel", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Checkbox("Fps", &showFpsWindow);
        if(ImGui::Button("Reset Camera pos")){
            camera.setRotation(-90.0f, 0.0f);
            camera.setPosition(glm::vec3(0.0f));
        }
        ImGui::SliderInt("n : ", &n, 0, 100);
        ImGui::Text("No. of cubes on screen: %d", n*n*n);
        ImGui::End();
       
        

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(renderer.getWindow());
        glfwPollEvents();
    }

    std::cout << glfwGetTime() << std::endl;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(renderer.getWindow());
    glfwTerminate();
    return 0;
}