#pragma once
#include <string>
#include <unordered_map>

class ShaderProgram{
    unsigned int rendererId;
    std::unordered_map<std::string, int> uniforms;

    public:
    ShaderProgram(std::string vsPath, std::string fsPath);
    void bind();
    int getUniformLocation(std::string uniform);
    ~ShaderProgram();
};