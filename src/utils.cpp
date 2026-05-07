#include "utils.hpp"
#include <fstream>
#include <iostream>



void loadShader(const std::string& filePath, std::string& shader){
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


static unsigned int compileShader(unsigned int type, const std::string& code){
    unsigned int id = glCreateShader(type);
    const char* src = &code[0];
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
