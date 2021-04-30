#ifndef __MESH__
#define __MESH__

#include <string>
#include <vector>
#include <list>

#include <core/GL/glew.h>
#include <core/GL/freeglut.h>
#include <core/glm/glm.hpp>
#include <core/glm/gtc/type_ptr.hpp>
#include <core/glm/gtx/string_cast.hpp>

#include "core/Utility.hpp"

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
};

class Mesh {
public:
    Mesh (const std::vector<vertex> vertices, const std::vector<unsigned int> indices) {
        this->vertices = vertices;
        this->indices = indices;
        // setupMesh 를 여기에 코딩
    }
    void setBoundingBox (const std::vector<glm::vec3>& bbVertices) {
        // 여기서 bounding box를 활용하여 메시를 그리려면 어떻게?
    }
    void pushVertex (const vertex& v) {
        vertices.push_back(v);
    }
    void pushIndex (const unsigned int i) {
        indices.push_back(i);
    }

private:
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;

private:
    unsigned int VAO, VBO, EBO;
};

#endif