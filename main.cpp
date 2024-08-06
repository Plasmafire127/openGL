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
#include "camera.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//camera
Camera camera;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = 400, lastY = 300;
bool firstMouse = true;

int main() 
    {
    glfwInit(); //initializes the glfw library, allowing us to configure below
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //sets configs for the next call to glfwCreateWindow();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //first argument targets the option to configure, second argument sets the value of the target
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //set for minimal features
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //macos specific

    unsigned int viewportWidth = 800;
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //cursor capture
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

//vertex&fragment shader stuff

float floor[] = {
    0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
     0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, -1.0f, -1.0f,  // bottom left
    -0.5f,  0.5f, 0.0f, -1.0f, 1.0f   // top left 

};

float vertices[] = {
    //vertices            //texture coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

//positions for each cube
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};


unsigned int Indices[] = 
{  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  

VBO vbo(sizeof(vertices), vertices);
EBO ebo(sizeof(vertices), Indices);
VBO vboFloor(sizeof(floor), floor);
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

TEXTURE texture2;
texture2.flipOnLoad(true);
texture2.createImage("/Users/jake/Desktop/opengl/images/grass.jpg",0,0,0,GL_RGB);
texture2.mipmap();

while(!glfwWindowShouldClose(window)) //render loop to keep drawing frames
{
    //deltaTime
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;  

    //inputs
    processInput(window);

    //rendering commands
    glClearColor(0.0f,0.0f,0.0f,1.0f); //state setting function, sets color to use on clear
    glClear(GL_COLOR_BUFFER_BIT); //state-using function using the current set state (^) to clear with
    shaderProgram.activate();

    shaderProgram.setInt("texture1",0);
    texture1.setActiveTexture(GL_TEXTURE0);
    vao.linkVBO(vbo, 0,1);


    //depth testing
    glEnable(GL_DEPTH_TEST);  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe

    //camera
    //view matrix (view space)
    TRANSFORM view;
    view.ID = camera.getLookAtMatrix();

    //projection matrix (clipping space)
    TRANSFORM projection;
    projection.perspective(camera.Fov, 800.0f, 600.0f);

    //send matrices to shader
    view.update(shaderProgram, "view");
    projection.update(shaderProgram, "projection");

    for(unsigned int i = 0; i < 10; i++)
    {
        //model matrix (local space)
        TRANSFORM model;
        model.translate(cubePositions[i]);
        float angle = (5*i) + 20.0f * glfwGetTime();
        model.rotate(angle, 1.0f, 0.3f, 0.5f);
        model.update(shaderProgram, "model");
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //floor
    TRANSFORM model;
    model.translate(0.0,-1.0,0.0);
    model.rotate(90,1.0,0.0,0.0);
    model.scale(100.0f,100.0f,100.0f);
    model.update(shaderProgram, "model");
    vao.linkVBO(vboFloor, 0, 1);
    texture2.setActiveTexture(0);
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
    const float cameraSpeed = 0.05f; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
            
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
    
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}