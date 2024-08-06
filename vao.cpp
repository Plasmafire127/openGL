#include "vao.h"
#include <sys/types.h>
#include <glad/glad.h>

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::linkVBO(VBO& VBO, GLuint layout0, GLuint layout1)
{
    VBO.bind();
    //position attribute
    glVertexAttribPointer(layout0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(layout1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    VBO.unbind();
}

void VAO::bind()
{
    glBindVertexArray(ID);
    
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::dispose()
{
    glDeleteVertexArrays(1, &ID);
}

//glVertexAttribPointer args:
//arg1: attribute to configure based on location
//arg2: size of the attribute
//arg 3: data type
//arg4: normalize data?
//arg5: stride: space between consecutive vertex attributes (bytes)
//arg6 offset in which the first attribute is located 