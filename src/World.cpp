#include "World.hpp"

/* // grid
World::World(const glm::vec4 color) {
    setColor(color);
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> lastLineIdx;
    float z = -AXIS_LIMIT_ABS;
    bool flag = true;
    unsigned int vertexCount = 0;
    while (z <= AXIS_LIMIT_ABS) {
        float x = -AXIS_LIMIT_ABS;
        while (x <= AXIS_LIMIT_ABS) {
            Vertex v;
            v.pos.x = x;
            v.pos.y = 0.0f;
            v.pos.z = z;
            v.norm.x = 0.0f;
            v.norm.y = 1.0f;
            v.norm.z = 0.0f;
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
    pushMesh(vertices, indices, -1);
    setDraw(true);
}
*/

World::World(const std::string backgroundImagePath) {
    setColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    std::vector<Vertex> ground_vertices, front_vertices;
    std::vector<unsigned int> indices;
    unsigned int texture;

    Vertex ground_rt, ground_rb, ground_lb, ground_lt;
    
    ground_rt.pos = glm::vec3(AXIS_LIMIT_ABS, 0.0f, -AXIS_LIMIT_ABS);
    ground_rt.norm = glm::vec3(0.0f, 1.0f, 0.0f);
    ground_rt.textureCoord = glm::vec2(1.0f, 1.0f);

    ground_rb.pos = glm::vec3(AXIS_LIMIT_ABS, 0.0f, AXIS_LIMIT_ABS);
    ground_rb.norm = glm::vec3(0.0f, 1.0f, 0.0f);
    ground_rb.textureCoord = glm::vec2(1.0f, 0.0f);

    ground_lb.pos = glm::vec3(-AXIS_LIMIT_ABS, 0.0f, AXIS_LIMIT_ABS);
    ground_lb.norm = glm::vec3(0.0f, 1.0f, 0.0f);
    ground_lb.textureCoord = glm::vec2(0.0f, 0.0f);

    ground_lt.pos = glm::vec3(-AXIS_LIMIT_ABS, 0.0f, -AXIS_LIMIT_ABS);
    ground_lt.norm = glm::vec3(0.0f, 1.0f, 0.0f);
    ground_lt.textureCoord = glm::vec2(0.0f, 1.0f);

    ground_vertices.push_back(ground_rt);
    ground_vertices.push_back(ground_rb);
    ground_vertices.push_back(ground_lb);
    ground_vertices.push_back(ground_lt);

    Vertex front_rt, front_rb, front_lb, front_lt;

    front_rt.pos = glm::vec3(AXIS_LIMIT_ABS, AXIS_LIMIT_ABS, -AXIS_LIMIT_ABS);
    front_rt.norm = glm::vec3(0.0f, 0.0f, -1.0f);
    front_rt.textureCoord = glm::vec2(1.0f, 1.0f);

    front_rb.pos = glm::vec3(AXIS_LIMIT_ABS, -AXIS_LIMIT_ABS, -AXIS_LIMIT_ABS);
    front_rb.norm = glm::vec3(0.0f, 0.0f, -1.0f);
    front_rb.textureCoord = glm::vec2(1.0f, 0.0f);

    front_lb.pos = glm::vec3(-AXIS_LIMIT_ABS, -AXIS_LIMIT_ABS, -AXIS_LIMIT_ABS);
    front_lb.norm = glm::vec3(0.0f, 0.0f, -1.0f);
    front_lb.textureCoord = glm::vec2(0.0f, 0.0f);

    front_lt.pos = glm::vec3(-AXIS_LIMIT_ABS, AXIS_LIMIT_ABS, -AXIS_LIMIT_ABS);
    front_lt.norm = glm::vec3(0.0f, 0.0f, -1.0f);
    front_lt.textureCoord = glm::vec2(0.0f, 1.0f);

    front_vertices.push_back(front_rt);
    front_vertices.push_back(front_rb);
    front_vertices.push_back(front_lb);
    front_vertices.push_back(front_lt);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int w, h, ch;
    unsigned char* pixelData = stbi_load(backgroundImagePath.c_str(), &w, &h, &ch, 0);
    if (pixelData) {
        GLenum channel;
        switch (ch) {
        case 1: channel = GL_RED; break;
        case 3: channel = GL_RGB; break;
        case 4: channel = GL_RGBA; break;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, channel, w, h, 0, channel, GL_UNSIGNED_BYTE, pixelData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "WARNING::TEXTURE::FAILED_TO_LOAD_AT_PATH: " << backgroundImagePath << std::endl;
    }
    stbi_image_free(pixelData);

    pushMesh(ground_vertices, indices, texture);
    pushMesh(front_vertices, indices, texture);
    setDraw(true);
}