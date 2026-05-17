#include <glad/glad.h>

#include <fstream>
#include <iostream>

#include "Shader.hpp"

void printMat4(glm::mat4 matrix){
    matrix = glm::transpose(matrix);
    std::cout << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << " " << matrix[0][3] << std::endl;
    std::cout << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << " " << matrix[1][3] << std::endl;
    std::cout << matrix[2][0] << " " << matrix[2][1] << " " << matrix[2][2] << " " << matrix[2][3] << std::endl;
    std::cout << matrix[3][0] << " " << matrix[3][1] << " " << matrix[3][2] << " " << matrix[3][3] << std::endl;

}

static void loadShader(const std::string& filePath, std::string& shader){
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filePath << std::endl;

        return;
    }
    std::string line;
    while(getline(file, line)){
        shader = shader+line+"\n";
    }
    std::cout << shader << std::endl;
    file.close();
}

static unsigned int compileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = &source[0];
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(!result){
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char message[len];
        glGetShaderInfoLog(id, len, &len, message);
        
        std::cout << "Failed to compile " <<
                    ((type == GL_VERTEX_SHADER)? "Vertex ":"Fragment ") <<
                    "Shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
 
    return id;
}

unsigned int createProgram(const std::string& vertex, const std::string& fragment){
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertex);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragment);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


ShaderProgram::ShaderProgram(std::string vsPath, std::string fsPath)
 : rendererId(0){
    rendererId = glCreateProgram();
    std::string vertex, fragment;

    std::cout << "Loading vertex shader:" << std::endl;
    loadShader(vsPath, vertex);
    std::cout << "Loading fragment shader:" << std::endl;
    loadShader(fsPath, fragment);

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertex);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragment);

    glAttachShader(rendererId, vs);
    glAttachShader(rendererId, fs);

    glLinkProgram(rendererId);
    glValidateProgram(rendererId);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void ShaderProgram::bind(){
    glUseProgram(rendererId);
}

int ShaderProgram::getUniformLocation(std::string uniform){

    if(uniforms.find(uniform) != uniforms.end()) return uniforms[uniform];

    int location = glGetUniformLocation(rendererId, &uniform[0]);
    if(location == -1) std::cout << "Warning: Uniform '" << uniform << "' does not exist." << std::endl;
    uniforms[uniform] = location;
    return location;
}

void ShaderProgram::setVec4f(std::string uniform, glm::vec4 vec4){
    int location = this->getUniformLocation(uniform);
    glUniform4f(location, vec4.x, vec4.y, vec4.z, vec4.w);
}

void ShaderProgram::setInt(std::string uniform, int n){
    int location = this->getUniformLocation(uniform);
    glUniform1i(location, n);
}

void ShaderProgram::setMat4f(std::string uniform, glm::mat4 &mat){
    int location = this->getUniformLocation(uniform);
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setVec3f(std::string uniform, glm::vec3 vec3){
    int location = this->getUniformLocation(uniform);
    glUniform3f(location, vec3.x, vec3.y, vec3.z);
}

void ShaderProgram::setFloat(std::string uniform, float n){
    int location = this->getUniformLocation(uniform);
    glUniform1f(location, n);
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(rendererId);
}