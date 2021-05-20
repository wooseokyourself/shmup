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
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        unsigned int vertexShader = readAndCompileShader(vertexShaderPath, GL_VERTEX_SHADER);
        unsigned int fragmentShader = readAndCompileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
        ID = linkShaders(vertexShader, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    bool setUniformInt(const std::string& name, const int data) {
        unsigned int uni = glGetUniformLocation(ID, name.c_str());
        glUniform1i(uni, data);
        return uni;
    }
    bool setUniformFloat(const std::string& name, const float data) {
        unsigned int uni = glGetUniformLocation(ID, name.c_str());
        glUniform1f(uni, data);
        return uni;
    }
    bool setUniformMat3(const std::string& name, const glm::mat3 data) {
        unsigned int uni = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix3fv(uni, 1, GL_FALSE, glm::value_ptr(data));
        return uni;
    }
    bool setUniformMat4(const std::string& name, const glm::mat4 data) {
        unsigned int uni = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(data));
        return uni;
    }
    bool setUniformVec3(const std::string& name, const glm::vec3& data) {
        unsigned int uni = glGetUniformLocation(ID, name.c_str());
        glUniform3fv(uni, 1, glm::value_ptr(data));
        return uni;
    }
    bool setUniformVec4(const std::string& name, const glm::vec4& data) {
        unsigned int uni = glGetUniformLocation(ID, name.c_str());
        glUniform4fv(uni, 1, glm::value_ptr(data));
        return uni;
    }
    void bind() {
        glUseProgram(ID);
    }
    void unbind() {
        glUseProgram(0);
    }

private:
    unsigned int readAndCompileShader(const std::string& shaderPath, const unsigned int type) const {
        // Read source code
        std::string _shaderCode;
        std::ifstream shaderFile;
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            shaderFile.open(shaderPath);
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
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
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            exit(EXIT_FAILURE);
        }
        return shader;
    }

    unsigned int linkShaders(const unsigned int vertexShader, const unsigned int fragmentShader) const {
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