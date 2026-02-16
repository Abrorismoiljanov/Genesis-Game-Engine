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

struct SubMesh{
    unsigned int VBO = 0;
    unsigned int VAO = 0;
    unsigned int EBO = 0;

    size_t IndexCount = 0;
    AssetHandle MaterialHandle;


    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
 
};

class ModelAsset : public Asset{
public:
    static constexpr AssetType StaticType = AssetType::Mesh;

    ModelAsset() { Type = AssetType::Mesh; }

    std::vector<SubMesh> SubMeshes;

};

