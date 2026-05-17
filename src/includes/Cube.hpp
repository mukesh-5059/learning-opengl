#pragma once
#include <glm/glm.hpp>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class Cube{
    glm::vec3 pos, rotation;
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
    static glm::mat4 baseMat;

    public:
    Cube();
    void draw(glm::vec3 pos, float angle, ShaderProgram &shader);
    ~Cube(){}

};

