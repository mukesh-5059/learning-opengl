#include <glad/glad.h>

#include "VertexArray.hpp"


void VertexArrayLayout::add(unsigned int type, unsigned int count, bool normalized){
    unsigned int s = count;
    switch(type){
        case GL_FLOAT: s *= sizeof(float); break;
    }
    vertexAttribute v = {type, count, normalized, s};
    vertexAttributes.push_back(v);
    vertexSize += s;
}

VertexArray::VertexArray(){
    glGenVertexArrays(1, &rendererId);
}

void VertexArray::bindLayout(const VertexBuffer& vb, const VertexArrayLayout& layout){
    bind();
    vb.bind();
    long int offset = 0;
    for(unsigned int i = 0; i<layout.vertexAttributes.size(); i++){
        const auto& element = layout.vertexAttributes[i];
        glVertexAttribPointer(i
                            , element.count, element.type
                            , element.normalized, layout.vertexSize    
                            , (const void*)offset);      //pointer of attribute inside the vertex
        glEnableVertexAttribArray(i);
        offset +=  element.stride;
    }
}

void VertexArray::bind(){
    glBindVertexArray(rendererId);
}

void VertexArray::unbind(){
    glBindVertexArray(0);
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &rendererId);
}

