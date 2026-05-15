#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera{
    glm::vec3 pos, up, direction;
    float speed;

    public:
    Camera();
    
    void input(GLFWwindow* window, float dt);
    void setPosition(glm::vec3 pos);
    void setDirection(glm::vec3 direction);
    glm::mat4 getLookAt();

    glm::vec3 getPos(){return pos;}
    glm::vec3 getDirection(){return direction;}
    float getSpeed(){return speed;}

    ~Camera();
};