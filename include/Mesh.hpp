#ifndef __MESH__
#define __MESH__

#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};

class Mesh {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
        void draw() {
        }

    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
};  

#endif