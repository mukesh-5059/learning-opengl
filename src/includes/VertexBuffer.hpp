#pragma once

class VertexBuffer{
    unsigned int rendererId;

    public:
    VertexBuffer(const void* data, unsigned int size);
    void bind() const;
    void unbind() const;
    
    ~VertexBuffer();
};