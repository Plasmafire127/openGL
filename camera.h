#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "transform.h"
#include <iostream>


class Camera
{
    public:
    //camera attributes
    glm::vec3 Position; 
    glm::vec3 Front; 
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
    float Speed;
    float Sensitivity;
    float Fov;

    //used in movement
    glm::vec3 Up; 
    glm::vec3 Right; 


    //constructor
    Camera()
    {
        Position = glm::vec3(0.0f, 0.0f, 3.0f);
        Front = glm::vec3(0.0f, 0.0f, -1.0f);
        WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        Speed = 0.2f;
        Sensitivity =0.2f;
        Fov = 45.0f;
        Yaw = -90.0f;
        Pitch = 0.0f;
    }

    //returns lookAt view matrix
    glm::mat4 getLookAtMatrix()
    {
        return lookAt(Position, (Position + Front), WorldUp);
    }


    void processKeyboardInput(GLFWwindow *window)
    {
        const float cameraSpeed = 0.05f; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            Position += Front * Speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            Position -= Front * Speed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            Position -= Right * Speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            Position += Right * Speed;
        
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= Sensitivity;
        yoffset *= Sensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }


    void ProcessMouseScroll(float yoffset)
    {
        Fov -= (float)yoffset;
        if (Fov < 1.0f)
            Fov = 1.0f;
        if (Fov > 45.0f)
            Fov = 45.0f;
    }

    void updateCameraVectors()
    {
        // calculate the new Front vector
        std::cout<<Front.x <<Front.y <<Front.z<<std::endl;
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        std::cout<<Front.x <<Front.y <<Front.z<<std::endl;
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }

};
#endif