#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include "imgui/imgui.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : pos(position), worldUp(up), yaw(yaw), pitch(pitch), 
      movementSpeed(2.5f), mouseSensitivity(0.1f), fov(45.0f), firstClick(true) {
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    
    right = glm::normalize(glm::cross(front, worldUp));
    this->up = glm::normalize(glm::cross(right, front));
}

void Camera::captureInput(GLFWwindow* window, float dt) {
    ImGuiIO& io = ImGui::GetIO();
    float velocity = movementSpeed * dt;

    if (!io.WantCaptureKeyboard) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos += front * velocity;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos -= front * velocity;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos -= right * velocity;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos += right * velocity;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) pos += worldUp * velocity;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) pos -= worldUp * velocity;
    }

    if (!io.WantCaptureMouse) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);

            int width, height;
            glfwGetWindowSize(window, &width, &height);

            if (firstClick) {
                glfwSetCursorPos(window, width / 2.0, height / 2.0);
                firstClick = false;
                return;
            }

            float xOffset = (float)(mouseX - (width / 2.0));
            float yOffset = (float)((height / 2.0) - mouseY);

            glfwSetCursorPos(window, width / 2.0, height / 2.0);

            yaw += xOffset * mouseSensitivity;
            pitch += yOffset * mouseSensitivity;

            pitch = std::clamp(pitch, -89.0f, 89.0f);

            updateCameraVectors();
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            firstClick = true;
        }
    }
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(pos, pos + front, up);
}

glm::mat4 Camera::getProjectionMatrix(int width, int height) {
    float aspect = (float)width / (float)height;
    return glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
}

void Camera::setRotation(float newYaw, float newPitch) {
    yaw = newYaw;
    pitch = newPitch;
    updateCameraVectors();
}