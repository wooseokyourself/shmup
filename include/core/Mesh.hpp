#ifndef __MESH__
#define __MESH__

#include <string>
#include <vector>

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
    void pushBackVertex (const vertex& v) {
        vertices.push_back(v);
    }
    void pushBackIndex (const unsigned int i) {
        indices.push_back(i);
    }
    void setBoundingBox (const std::vector<glm::vec3>& bbVertices) {
        // 여기서 bounding box를 활용하여 메시를 그리려면 어떻게?
    }

private:
    void setupMesh() {

    }

private:
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;

private:
    unsigned int VAO, VBO, EBO;
};

#endif