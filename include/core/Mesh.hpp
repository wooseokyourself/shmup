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
    glm::vec3 textureCoord;
};

struct Texture {
    unsigned int ID;
    std::string type; // diffuse or specular
};

namespace TextureType {
    const std::string diffuse = "diffuse";
    const std::string specular = "specular";
    const std::string ambient = "ambient";
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

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoord));

        glBindVertexArray(0);
    }
    void draw(Shader* shader) {
        /* // multi texturing
        int diffuseN = 0, specularN = 0, ambientN = 0;
        for (int unit = 0; unit < textures.size(); unit++) {
            glActiveTexture(GL_TEXTURE0 + unit); // texture unit
            
            std::string samplerName;
            switch (textures[unit].type) {
                case TextureType::diffuse:
                    samplerName = TextureType::diffuse + std::to_string(diffuseN++);
                    break;
                case TextureType::specular:
                    samplerName = TextureType::specular + std::to_string(specularN++);
                    break;
                case TextureType::ambient:
                    samplerName = TextureType::ambient + std::to_string(ambientN++);
                    break;
            }
            shader->setUniformInt("material." + samplerName, unit);
            glBindTexture(GL_TEXTURE_2D, textures[unit].ID);
        }
        */

        // single texturing
        for (int unit = 0; unit < textures.size(); unit++) {
            glActiveTexture(GL_TEXTURE0 + unit);
            std::string samplerName;
            switch (textures[unit].type) {
                case TextureType::diffuse:
                    samplerName = TextureType::diffuse;
                    break;
                case TextureType::specular:
                    samplerName = TextureType::specular;
                    break;
                case TextureType::ambient:
                    samplerName = TextureType::ambient;
                    break;
            }
            shader->setUniformInt("material." + samplerName, unit);
            glBindTexture(GL_TEXTURE_2D, textures[unit].ID);
        }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

private:
    unsigned int VAO, VBO, EBO;
};

#endif