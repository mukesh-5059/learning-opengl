#include <glad/glad.h>
#include <VertexBuffer.hpp>

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    glGenBuffers(1, &rendererId);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void VertexBuffer::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}
void VertexBuffer::unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &rendererId);
}
