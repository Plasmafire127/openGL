//include guards. stops file from being included more than once in the same file
#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "vbo.h"


class VAO
{
    public: 
    GLuint ID; //bind ID
    VAO(); //constructor generates VAO with ID
    // utility uniform functions

    // Links a VBO to the VAO - generating and enabling a vertex attribute pointer
    void linkVBO(VBO& VBO, GLuint layout0, GLuint layout1, GLuint layout2); //vertex attributes
    void bind(); //bind to a buffer
    void unbind(); //unbinds buffer
    void dispose();
};

#endif