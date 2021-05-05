#include "World.hpp"

World::World() {
    setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> lastLineIdx;
    float z = -AXIS_LIMIT_ABS;
    bool flag = true;
    unsigned int vertexCount = 0;
    while (z <= AXIS_LIMIT_ABS) {
        float x = -AXIS_LIMIT_ABS;
        while (x <= AXIS_LIMIT_ABS) {
            vertex v;
            v.position.x = x;
            v.position.y = 0.0f;
            v.position.z = z;
            vertices.push_back(v);
            vertexCount++;
            if (flag) // 밑으로
                z += TILE_LEN;
            else { // 위로
                x += TILE_LEN;
                z -= TILE_LEN;
            }
            if (x > AXIS_LIMIT_ABS)
                z += TILE_LEN;
            flag = !flag;
        }
        lastLineIdx.push_back(vertexCount);
    }
    unsigned int begin = 2;
    for (int i = 0; i < lastLineIdx.size(); i++) {
        unsigned int end = lastLineIdx[i];
        for (unsigned int third = begin; third < end; third++) {
            unsigned int first = third == begin ? begin - 2 : indices[indices.size() - 2];
            unsigned int second = third == begin ? begin - 1 : indices[indices.size() - 1];
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(third);
        }
        begin = end + 2;
    }
    meshes.push_back(Mesh(vertices, indices));
    setDraw(true);
}