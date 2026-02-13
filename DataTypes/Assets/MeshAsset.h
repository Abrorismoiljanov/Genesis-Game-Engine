#pragma once
#include "unordered_map"
#include "string"
#include "MaterialAsset.h"
#include <vector>
#include <cstdint>
#include <glm/glm.hpp>

struct Vertex{
    glm::vec3 position;  
    glm::vec3 normal;    
    glm::vec2 uv;        
};

struct Mesh{
    unsigned int VAO, VBO, EBO = 0;
    size_t IndexCount = 0;
    MaterialData Mat;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

