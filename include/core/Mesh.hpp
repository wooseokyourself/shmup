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
    glm::vec2 textureCoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, const unsigned int diffuseMap, const unsigned int normalMap) {
        this->vertices = vertices;
        this->indices = indices;
        this->diffuseMap = diffuseMap;
        this->normalMap = normalMap;
        this->hasTexture = diffuseMap != UINT_MAX ? true : false;
        
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoord));
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

        glBindVertexArray(0);
    }
    void draw(Shader* shader) {
        if (hasTexture) {
            shader->setUniformInt("hasTexture", true);

            glActiveTexture(GL_TEXTURE0);
            shader->setUniformInt("textureDiffuse", 0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);

            glActiveTexture(GL_TEXTURE1);
            shader->setUniformInt("textureNormal", 1);
            glBindTexture(GL_TEXTURE_2D, normalMap);
        }
        else
            shader->setUniformInt("hasTexture", false);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    void setTextureDiffuseMap(const unsigned int diffuseMap) {
        this->diffuseMap = diffuseMap;
    }

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int diffuseMap;
    unsigned int normalMap;
    bool hasTexture;

private:
    unsigned int VAO, VBO, EBO;
};

#endif