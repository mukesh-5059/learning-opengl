#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Cube.hpp"


static unsigned int indices[] = {
        0,  1,  2,  2,  3,  0,
        4,  5,  6,  6,  7,  4,
        8,  9,  10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

static float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f
    };

glm::mat4 Cube::baseMat = glm::mat4(1.0);
Cube::Cube()
 : pos(glm::vec3(0.0)), rotation(glm::vec3(0.0)),
   ibo(indices, sizeof(indices) / sizeof(unsigned int)),
   vbo(vertices, sizeof(vertices)) {

    VertexArrayLayout vl;
    vl.add(GL_FLOAT, 3, GL_FALSE);
    vl.add(GL_FLOAT, 2, GL_FALSE);
    vao.bindLayout(vbo, vl);
    vao.bind();
    ibo.bind();

}

void Cube::draw(glm::vec3 pos, float angle, ShaderProgram &shader){
    
    glm::mat4 modelMat = glm::translate(baseMat, pos);
    modelMat = glm::rotate(modelMat, angle, glm::vec3(1.0));
    shader.setMat4f("u_ModelMatrix", modelMat);
    glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, NULL);
}
