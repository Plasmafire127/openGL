//include guards. stops file from being included more than once in the same file
#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO
{
    public: 
    GLuint ID; //bind ID
    VBO(); //constructor
    VBO(GLsizeiptr size, GLfloat* vertices);
    
    void bind(); //bind to a buffer
    void unbind(); //unbinds buffer
    void setBufferData(GLsizeiptr size, GLfloat* vertices); //copies data into bound buffer
    void dispose();
};

#endif