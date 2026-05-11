#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "StbImage.h"

#include "Texture.hpp"

Texture::Texture(std::string path)
 : rendererId(0), path(path), localBuffer(NULL), width(0), height(0), bpp(0) {
    
    glGenTextures(1, &rendererId);
    bind();

    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(&path[0], &width, &height, &bpp, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 
        0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

    stbi_image_free(localBuffer);

    unbind();
}

void Texture::bind(unsigned int slot){
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, rendererId);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture(){
    glDeleteTextures(1, &rendererId);
}