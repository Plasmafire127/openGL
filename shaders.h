#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <cerrno>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  

std::string get_file_contents(const char * filename);

class Shader
{
    public:
        GLuint ID;
        Shader(const char* vFile, const char* fFile);
        void activate();
        void dispose();
        
        // utility uniform functions
        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
        GLuint getUniformLocation(const std::string uniform) const;

    private:
        int debugAllShaders(GLuint& vertexShader, GLuint& fragmentShader);
        int debugFragmentShader(GLuint& fragmentShader);
        int debugVertexShader(GLuint& vertexShader);
        int debugShaderProgram(); // uses ID of current Shader object
        // May be public later?
        GLuint loadFragmentShader(const char* fFile);
        GLuint loadVertexShader(const char* vFile);


};

#endif