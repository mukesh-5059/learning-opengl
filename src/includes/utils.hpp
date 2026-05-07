#pragma once
#include <string>
#include <glad/glad.h>

void loadShader(const std::string& filePath, std::string& shader);

unsigned int createProgram(const std::string& vertex, const std::string& fragment);