#pragma once
#include "glm/glm.hpp"
#include "string"

struct MaterialData{
    glm::vec4 albedo {1.0f};
    float textureScale = 1.0f;
    float metallic = 0.0f;
    float roughness = 1.0f;
    float emissiveIntensity = 0.0f;

    
    std::string albedoTexturePath;
    std::string normalTexturePath;
    std::string metallicTexturePath;
    std::string roughnessTexturePath;
    std::string emissiveTexturePath;
};

