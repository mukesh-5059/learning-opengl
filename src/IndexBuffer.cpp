#include <glad/glad.h>
#include <IndexBuffer.hpp>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):count(count){
    glGenBuffers(1, &rendererId);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
}

void IndexBuffer::unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const{
    return count;
}

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &rendererId);
}
