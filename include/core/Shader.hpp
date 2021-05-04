#ifndef __SHADER__
#define __SHADER__

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "core/Utility.hpp"

using namespace std;

class Shader {
public:
    Shader (const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        cout << "   Shader constructor start" << endl;
        unsigned int vertexShader = readAndCompileShader(vertexShaderPath, GL_VERTEX_SHADER);
        unsigned int fragmentShader = readAndCompileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
        ID = linkShaders(vertexShader, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        cout << "   Shader constructor end" << endl;
    }
    void use () {
        glUseProgram(ID);
    }
    void setBool (const std::string &name, const bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt (const std::string &name, const int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat (const std::string &name, const float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

private:
    unsigned int readAndCompileShader (const std::string& shaderPath, const unsigned int type) const {
        cout << "    Shader readAndCompile start: " << shaderPath << endl;
        // Read source code
        std::string _shaderCode;
        std::ifstream shaderFile;
        shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try {
            cout << "     Shader readAndCompile 1" << endl;
            shaderFile.open(shaderPath);
            cout << "     Shader readAndCompile 2" << endl;
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            cout << "     Shader readAndCompile 3" << endl;
            shaderFile.close();
            _shaderCode = shaderStream.str();
        }
        catch (std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Compile shaders
        int success;
        char infoLog[512];
        const char* shaderCode = _shaderCode.c_str();
        cout << "     Shader readAndCompile 4" << endl;
        unsigned int shader = glCreateShader(type);
        cout << "     Shader readAndCompile 5" << endl;
        glShaderSource(shader, 1, &shaderCode, NULL);
        cout << "     Shader readAndCompile 6" << endl;
        glCompileShader(shader);
        cout << "     Shader readAndCompile 7" << endl;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        cout << "     Shader readAndCompile 8" << endl;
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            exit(EXIT_FAILURE);
        }
        cout << "    Shader readAndCompile end" << endl;
        return shader;
    }

    unsigned int linkShaders (const unsigned int vertexShader, const unsigned int fragmentShader) const {
        int success;
        char infoLog[512];
        unsigned int shader = glCreateProgram();
        glAttachShader(shader, vertexShader);
        glAttachShader(shader, fragmentShader);
        glLinkProgram(shader);
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            shader = -1;
        }
        return shader;
    }

public:
    unsigned int ID;
};

#endif