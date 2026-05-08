#pragma once

class IndexBuffer{
    unsigned int rendererId;

    public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    void bind();
    void unbind();
    
    ~IndexBuffer();
};