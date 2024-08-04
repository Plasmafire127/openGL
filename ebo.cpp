#include "ebo.h"

EBO::EBO()
{
    glGenBuffers(1, &ID);
}

EBO::EBO(GLsizeiptr size, GLuint* indices)
{
    glGenBuffers(1, &ID);
    bind();
    setBufferData(size, indices);
}

void EBO::setBufferData(GLsizeiptr size, GLuint* indices)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); 
}

void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}

void EBO::dispose()
{
    glDeleteBuffers(1, &ID);
}