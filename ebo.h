//include guards. stops file from being included more than once in the same file
#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO
{
    public: 
    GLuint ID; //bind ID
    EBO(); //constructor
    EBO(GLsizeiptr size, GLuint* indices);
    
    void bind(); //bind to a buffer
    void unbind(); //unbinds buffer
    void setBufferData(GLsizeiptr size, GLuint* indices); //copies data into bound buffer
    void dispose();
};

#endif