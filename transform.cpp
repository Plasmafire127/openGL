#include "transform.h"
#include <../../glm/glm.hpp>
#include <../../glm/gtc/matrix_transform.hpp>
#include <../../glm/gtc/type_ptr.hpp>


TRANSFORM::TRANSFORM()
{
    ID = glm::mat4(1.0f);
}

void TRANSFORM::lookAt(glm::vec3 vec1, glm::vec3 vec2, glm::vec3 vec3)
{
    ID = glm::lookAt(vec1,vec2,vec3);
}

void TRANSFORM::reset()
{
    ID = glm::mat4(1.0f);
}

void TRANSFORM::scale(float x, float y, float z)
{
    ID = glm::scale(ID, glm::vec3(x,y,z));
}

void TRANSFORM::scale(glm::vec3 vec)
{
    ID = glm::scale(ID, vec);
}

void TRANSFORM::rotate(float degrees, float x, float y, float z)
{
    ID = glm::rotate(ID, glm::radians(degrees), glm::vec3(x,y,z));
}

void TRANSFORM::rotate(float degrees, glm::vec3 vec)
{
    ID = glm::rotate(ID, glm::radians(degrees), vec);
}


void TRANSFORM::translate(float x, float y, float z)
{
    ID = glm::translate(ID, glm::vec3(x,y,z));
}

void TRANSFORM::translate(glm::vec3 vec)
{
    ID = glm::translate(ID, vec);
}

void TRANSFORM::perspective(float FOVdegrees, float width, float height)
{
    ID = glm::perspective(glm::radians(FOVdegrees), width/height, 0.1f, 100.0f);
}


void TRANSFORM::update(Shader shader, const std::string uniform)
{
    glUniformMatrix4fv(shader.getUniformLocation(uniform), 1, GL_FALSE, glm::value_ptr(ID));
}

 