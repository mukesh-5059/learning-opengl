#pragma once
#include <string>
#include <unordered_map>

class ShaderProgram{
    unsigned int rendererId;
    std::unordered_map<std::string, int> uniforms;

    public:
    ShaderProgram(std::string vsPath, std::string fsPath);
    int getUniformLocation(std::string uniform);

    void setVec4f(std::string uniform, float v0, float v1, float v2, float v3);
    void setInt(std::string uniform, int n);

    void bind();
    ~ShaderProgram();
};