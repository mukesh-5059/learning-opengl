#pragma once
#include "VertexBuffer.hpp"
#include <vector>

struct vertexAttribute{
    unsigned int type;
    unsigned int count;
    bool normalized;
    unsigned int stride;
};

class VertexArrayLayout{
    public:
    std::vector<struct vertexAttribute> vertexAttributes;
    unsigned int vertexSize;

    VertexArrayLayout():vertexSize(0){}
    void push(unsigned int type, unsigned int count, bool normalized);
};

class VertexArray{
    unsigned int rendererId;

    public:
    VertexArray();
    void bindLayout(const VertexBuffer& vb, const VertexArrayLayout& layout);
    void bind();
    ~VertexArray();
}; 

