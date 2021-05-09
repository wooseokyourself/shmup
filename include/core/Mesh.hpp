#ifndef __MESH__
#define __MESH__

#include <string>
#include <vector>
#include <list>

#include "core/ModelViewMat.hpp"
#include "core/Shader.hpp"
#include "core/Utility.hpp"

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

class Mesh {
public:
    Mesh(const std::vector<glm::vec3> vertices, const std::vector<unsigned int> indices) {
        this->vertices = vertices;
        this->indices = indices;
        
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    }
    void draw() {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }   

private:
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

private:
    unsigned int VAO, VBO, EBO;
};

#endif