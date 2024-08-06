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

    //set lookAt fn
    void lookAt(glm::vec3 vec1, glm::vec3 vec2, glm::vec3 vec3);

    //function overloading may not be worth as you can just pass in vec(x,y,z) but meh

    //add scaling transform
    void scale(float x, float y, float z);
    void scale(glm::vec3 vec);

    //add rotational transform
    void rotate(float degrees, float x, float y, float z);
    void rotate(float degrees, glm::vec3 vec);

    //add translational transform
    void translate(float x, float y, float z);
    void translate(glm::vec3 vec);

    //set perspective transform
    void perspective(float FOVdegrees, float width, float height);

    //pass to vertex shader
    void update(Shader shader, const std::string uniform);
};

#endif