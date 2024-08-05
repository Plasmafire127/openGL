//include guards. stops file from being included more than once in the same file
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <../../glm/glm.hpp>
#include <../../glm/gtc/matrix_transform.hpp>
#include <../../glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "shaders.h"

class TRANSFORM
{
    public: 
    //object ID
    glm::mat4 ID; 
    //Create transform as identity matrix
    TRANSFORM(); 

    //reset transform to identity matrix
    void reset();

    //add scaling transform
    void scale(float x, float y, float z);

    //add rotational transform
    void rotate(float degrees, float x, float y, float z);

    //add translational transform
    void translate(float x, float y, float z);

    //pass to vertex shader
    void update(Shader shader);
};

#endif