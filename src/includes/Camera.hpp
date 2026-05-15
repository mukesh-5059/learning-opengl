#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Renderer.hpp"

class Camera{
    glm::vec3 pos, up, direction;
    float speed, fov;
    Renderer renderer;

    public:
    Camera(Renderer &renderer);
    
    void captureInput(float dt);
    void setPosition(glm::vec3 pos);
    void setDirection(glm::vec3 direction);
    glm::mat4 getLookAt();
    glm::mat4 getProj();

    glm::vec3 getPos(){return pos;}
    glm::vec3 getDirection(){return direction;}
    float getSpeed(){return speed;}

    ~Camera();
};