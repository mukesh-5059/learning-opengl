#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(Renderer &renderer)
 :  up(glm::vec3(0.0, 1.0, 0.0)),
    direction(glm::vec3(0.0, 0.0, -1.0)),
    pos(glm::vec3(0.0)),
    speed(2.0),
    fov(45.0),
    renderer(renderer) {

}

void Camera::captureInput(float dt){
    GLFWwindow *window = renderer.getWindow();
    float speed = dt * this->speed;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += speed * direction;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= speed * direction;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= glm::normalize(glm::cross(direction, up)) * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += glm::normalize(glm::cross(direction, up)) * speed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        pos += speed * up;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        pos -= speed * up;
}

glm::mat4 Camera::getLookAt(){
    return glm::lookAt(pos, pos+direction, up);
}

glm::mat4 Camera::getProj(){
    return glm::perspective(glm::radians(fov),
      (float)renderer.getWidth()/(float)renderer.getHeight(), 0.1f, 100.0f);
}

void Camera::setDirection(glm::vec3 direction){
    this->direction = direction;
}

void Camera::setPosition(glm::vec3 pos){
    this->pos = pos;
}

Camera::~Camera(){

}