#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>


#include "ebo.h"
#include "vbo.h"
#include "vao.h"
#include "shaders.h"
#include "stb_image.h" 
#include "texture.h"
#include "transform.h"


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

while(!glfwWindowShouldClose(window)) //render loop to keep drawing frames
{
    //inputs
    processInput(window);

    //rendering commands
    glClearColor(1.0f,1.0f,1.0f,1.0f); //state setting function, sets color to use on clear
    glClear(GL_COLOR_BUFFER_BIT); //state-using function using the current set state (^) to clear with
    shaderProgram.activate();

    //create indentity matrix
    TRANSFORM transform;
    transform.translate(1.0,1.0,0.0);
 
    shaderProgram.setInt("texture1",0);

    //set matrix
    transform.update(shaderProgram);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe

    //rectangle
    texture1.setActiveTexture(GL_TEXTURE0);
    vao.linkVBO(vbo, 0,1,2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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