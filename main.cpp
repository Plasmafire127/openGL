#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <../../glm/glm.hpp>
#include <../../glm/gtc/matrix_transform.hpp>
#include <../../glm/gtc/type_ptr.hpp>
#include <cstdlib> // For rand() and srand()

#include "ebo.h"
#include "vbo.h"
#include "vao.h"
#include "shaders.h"
#include "stb_image.h" 
#include "texture.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow *window);

int main() 
    {
    glfwInit(); //initializes the glfw library, allowing us to configure below
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //sets configs for the next call to glfwCreateWindow();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //first argument targets the option to configure, second argument sets the value of the target
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //set for minimal features
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //macos specific

    unsigned int viewportWidth = 600;
    unsigned int viewportHeight = 600; 


//WINDOW OBJECT
    GLFWwindow* window = glfwCreateWindow(viewportWidth, viewportHeight, "LearnOpenGL", NULL, NULL); //pointer, creates a window using configs set from glfwWindowHints above
    if (window==NULL)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    } 

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //loads the OS Specific address of openGLs function pointers
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);   //registers resize function, calling it on window resize

//vertex&fragment shader stuff

float vertices[] = 
{
    // positions          // colors           // texture coords
    1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
    1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};


unsigned int Indices[] = 
{  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  



VBO vbo(sizeof(vertices), vertices);
VBO vboHand(sizeof(vertices),vertices);
EBO ebo(sizeof(vertices), Indices);
VAO vao;
vao.bind();
ebo.bind();

Shader shaderProgram("../../shaders/vertexShader.glsl","../../shaders/fragmentShader.glsl");

//generate texture1 object
TEXTURE texture1;
texture1.flipOnLoad(true);
texture1.createImage("/Users/jake/Desktop/opengl/images/emoji.jpeg", 0, 0, 0, GL_RGB);

// set the texture wrapping parameters
texture1.textureWrap(GL_REPEAT);

// set texture filtering parameters
texture1.textureFilter(GL_TEXTURE_MIN_FILTER,GL_LINEAR);
texture1.mipmap();

TEXTURE textureHand;
textureHand.flipOnLoad(true);
textureHand.createImage("/Users/jake/Desktop/opengl/images/hand.png", 0, 0, 0, GL_RGBA);

//for translation
int frameCounter = 0;
float randomx = 0.0f;
float randomy = 0.0f;
int rotateCounter = 0;


while(!glfwWindowShouldClose(window)) //render loop to keep drawing frames
{
    //inputs
    processInput(window);

    //rendering commands
    glClearColor(1.0f,1.0f,1.0f,1.0f); //state setting function, sets color to use on clear
    glClear(GL_COLOR_BUFFER_BIT); //state-using function using the current set state (^) to clear with
    shaderProgram.activate();


    //transform things
    float timeValue = glfwGetTime();
    
    if(frameCounter % 8 == 0)
    {
        //generate value between 0-1
        randomx = float(rand()) / float(RAND_MAX);
        randomy = float(rand()) / float(RAND_MAX);
        //shift to -0.5 to 0.5
        randomx = randomx - 0.5f;
        randomy = randomy - 0.5f;
    }
    frameCounter++;

    //create indentity matrix
    glm::mat4 transform = glm::mat4(1.0f);
    //add a rotation (will apply second)
    //glm::move to bottom right
    transform = glm::translate(transform, glm::vec3(randomx,randomy,0.0f));
    //change transform matrix to rotate degrees based on time on z axis
    
    if(frameCounter % 4 == 0)
    {
        if(rotateCounter % 2 == 0)
        {
            transform = glm::rotate(transform, 0.5f, glm::vec3(0.0f,0.0f,1.0f));  
        }
        else
        {
            transform = glm::rotate(transform, -0.5f, glm::vec3(0.0f,0.0f,1.0f));
        }
        rotateCounter++;
    }
    transform = glm::scale(transform, glm::vec3(0.2,0.2,0.2));
    
    //need to make this part of shaders.cpp
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture1"), 0); // set it manually
    //glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture2"), 1); // set it manually

    unsigned int transformLoc = glGetUniformLocation(shaderProgram.ID, "transform");
    //set matrix
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe

    //rectangle
    texture1.setActiveTexture(GL_TEXTURE0);
    vao.linkVBO(vbo, 0,1,2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(randomx + 0.2,randomy + 0.2,0.0f));
    if(frameCounter % 4 == 0)
    {
        if(rotateCounter % 2 == 0)
        {
            transform = glm::rotate(transform, 0.5f, glm::vec3(0.0f,0.0f,1.0f));  
        }
        else
        {
            transform = glm::rotate(transform, -0.5f, glm::vec3(0.0f,0.0f,1.0f));
        }
        rotateCounter++;
    }
    transform = glm::scale(transform, glm::vec3(0.2,0.2,0.2));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    textureHand.setActiveTexture(GL_TEXTURE0);
    vao.linkVBO(vboHand, 0,1,2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //triangle
    //vao.linkVBO(vbo, 0,1,2);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    
    

    //check and call events and swap buffers
    glfwSwapBuffers(window); //two "frames", one with next drawn image and one with current. swaps when next drawn image is ready (I think?)
    glfwPollEvents(); //checks for inputs
}

    //cleanup time
    vao.dispose();    
    vbo.dispose();    
    ebo.dispose();    
    shaderProgram.dispose();
    texture1.dispose();
    //texture2.dispose();
    glfwTerminate(); //clean/delete all glfw allocated resources

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) //recalls viewport with new resized window
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}