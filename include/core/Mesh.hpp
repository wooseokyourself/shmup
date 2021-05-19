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

struct Vertex {
    glm::vec3 pos;
    glm::vec3 norm;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices) {
        this->vertices = vertices;
        this->indices = indices;
        
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));

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
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

private:
    unsigned int VAO, VBO, EBO;
};

#endif