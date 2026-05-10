#pragma once

class IndexBuffer{
    unsigned int rendererId;
    unsigned int count;

    public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    void bind();
    void unbind();
    unsigned int getCount() const;
    
    ~IndexBuffer();
};