#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

void printMat4(glm::mat4 proj);

class ShaderProgram{
    unsigned int rendererId;
    std::unordered_map<std::string, int> uniforms;

    public:
    ShaderProgram(std::string vsPath, std::string fsPath);
    int getUniformLocation(std::string uniform);

    void setVec4f(std::string uniform, glm::vec4 vec4);
    void setVec3f(std::string uniform, glm::vec3 vec3);
    void setInt(std::string uniform, int n);
    void setFloat(std::string uniform, float n);
    void setMat4f(std::string uniform, glm::mat4 &mat);

    void bind();
    ~ShaderProgram();
};