#include "vbo.h"

VBO::VBO()
{
    glGenBuffers(1, &ID);
}

VBO::VBO(GLsizeiptr size, GLfloat* vertices)
{
    glGenBuffers(1, &ID);
    bind();
    setBufferData(size, vertices);
}

void VBO::setBufferData(GLsizeiptr size, GLfloat* vertices)
{
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID); 
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}

void VBO::dispose()
{
    glDeleteBuffers(1, &ID);
}