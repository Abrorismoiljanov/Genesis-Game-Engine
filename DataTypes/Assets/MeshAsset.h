#pragma once
#include <vector>
#include <cstdint>
#include "Asset.h"
#include "glm/glm.hpp"
#include "GL/glew.h"

struct Vertex{
    glm::vec3 position;  
    glm::vec3 normal;    
    glm::vec2 uv;        
};

struct Mesh{
    unsigned int VBO = 0;
    unsigned int VAO = 0;
    unsigned int EBO = 0;

    size_t IndexCount = 0;


    Mesh() = default;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&&) noexcept = default;

    Mesh& operator=(Mesh&&) noexcept = default;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
 
};

class MeshAsset : public Asset{
public:
    static constexpr AssetType StaticType = AssetType::Mesh;

    MeshAsset() { Type = AssetType::Mesh; }

    std::vector<Mesh> meshes;

};

