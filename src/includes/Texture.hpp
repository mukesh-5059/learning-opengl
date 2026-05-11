#pragma once
#include <string>

class Texture{
    unsigned int rendererId;
    std::string path;
    unsigned char *localBuffer;
    int width, height, bpp;

    public:
    Texture(std::string path);
    void bind(unsigned int slot = 0);
    void unbind();

    ~Texture();
};