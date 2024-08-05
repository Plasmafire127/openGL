//include guards. stops file from being included more than once in the same file
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>
#include "stb_image.h" 
#include <../../glm/glm.hpp>
#include <../../glm/gtc/matrix_transform.hpp>
#include <../../glm/gtc/type_ptr.hpp>

class TEXTURE
{
    public: 
    GLuint ID; //object ID

    //create texture object
    TEXTURE(); 

    void flipOnLoad(bool boolean);

    void bind(); 
    void unbind(); 
    void dispose();

    //set wrap mode
    void textureWrap(GLenum wrapMode);
    //set filter mode
    void textureFilter(GLenum scale, GLenum filterMode);
    //border color fn?

    //create mipmap
    void mipmap();

    //glActiveTexture() and bind()
    void setActiveTexture(GLenum textureIndex);

    //bind, load, and generate image
    void createImage(const std::string& filepath, int width, int height, int nrChannels, GLenum rgba);
};

#endif