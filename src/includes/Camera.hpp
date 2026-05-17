#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
private:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float fov;

    bool firstClick;

    void updateCameraVectors();

public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
           float yaw = -90.0f, 
           float pitch = 0.0f);

    void captureInput(GLFWwindow* window, float dt);
    
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix(int width, int height);

    glm::vec3 getPosition() const { return pos; }
    void setPosition(glm::vec3 newPos) { pos = newPos; }
    void setRotation(float newYaw, float newPitch);
    
    float getSpeed() const { return movementSpeed; }
    void setSpeed(float speed) { movementSpeed = speed; }
};