#include "transform.h"
#include <../../glm/glm.hpp>
#include <../../glm/gtc/matrix_transform.hpp>
#include <../../glm/gtc/type_ptr.hpp>

TRANSFORM::TRANSFORM()
{
    ID = glm::mat4(1.0f);
}


void TRANSFORM::reset()
{
    ID = glm::mat4(1.0f);
}

void TRANSFORM::scale(float x, float y, float z)
{
    ID = glm::scale(ID, glm::vec3(x,y,z));
}
void TRANSFORM::rotate(float degrees, float x, float y, float z)
{
    ID = glm::rotate(ID, glm::radians(degrees), glm::vec3(x,y,z));
}
void TRANSFORM::translate(float x, float y, float z)
{
    ID = glm::translate(ID, glm::vec3(0.5,0.5,0.5));
}

void TRANSFORM::update(Shader shader)
{
    glUniformMatrix4fv(shader.getUniformLocation("transform"), 1, GL_FALSE, glm::value_ptr(ID));
}