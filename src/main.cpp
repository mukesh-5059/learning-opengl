#include "utils.hpp"
#include "GLFW/glfw3.h"
#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    { 
        glfwTerminate();
        return -1; 
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    int version = gladLoadGL();
    if (version == 0) {
        std::cout << "Failed to initialize OpenGL context\n" << std::endl;
        return -1;
    }
    std::cout << "loaded " << glGetString(GL_VERSION) << std::endl;


    float pos[6] = {
         0, 0.5,
         -0.5, 0,
         0.5, 0
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);


    std::string vertexShader, fragmentShader;
    loadShader("res/shaders/vertex.shader", vertexShader);
    loadShader("res/shaders/fragment.shader", fragmentShader);


    unsigned int prog = createProgram(vertexShader, fragmentShader);
    glUseProgram(prog);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) )
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        
        glDrawArrays(GL_TRIANGLES, 0, 3);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(prog);

    glfwTerminate();
    return 0;
}