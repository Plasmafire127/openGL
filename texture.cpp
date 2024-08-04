#include <glad/glad.h>
#include "texture.h"
#include "stb_image.h" 
#include <iostream>

TEXTURE::TEXTURE()
{
    glGenTextures(1, &ID);
}

void TEXTURE::flipOnLoad(bool boolean)
{
    stbi_set_flip_vertically_on_load(boolean);  
}
void TEXTURE::createImage(const std::string& filepath, int width, int height, int nrChannels, GLenum rgba)
{
    //random code i found to enable alpha
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    //must bind before generating image
    bind();
    
    //load image
    const char* file = filepath.c_str();
    unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);

    //generate image, may need to modify for RGBA arguments
        if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, rgba, width, height, 0, rgba, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    //is this spot right?
    stbi_image_free(data);
}

void TEXTURE::textureWrap(GLenum wrapMode)
{
    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // White border color
    switch(wrapMode)
    {
        case GL_REPEAT:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case GL_MIRRORED_REPEAT:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
        case GL_CLAMP_TO_EDGE:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case GL_CLAMP_TO_BORDER:
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            break;
        default:
            std::cerr << "Invalid texture wrap mode" << std::endl;
            return;
    }
}

void TEXTURE::textureFilter(GLenum scale, GLenum filterMode)
{
    glTexParameteri(GL_TEXTURE_2D, scale, filterMode);
}

void TEXTURE::mipmap()
{
    glGenerateMipmap(GL_TEXTURE_2D);
}

void TEXTURE::setActiveTexture(GLenum textureIndex)
{
    glActiveTexture(textureIndex);
    bind();
}

void TEXTURE::bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void TEXTURE::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

//not sure if this is right
void TEXTURE::dispose()
{
    glDeleteTextures(1, &ID);
}