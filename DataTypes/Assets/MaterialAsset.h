#pragma once
#include "glm/glm.hpp"
#include "string"

struct MaterialData{
    glm::vec4 albeddo {1.0f, 1.0f, 1.0f, 1.0f};
    std::string albedoTexturePath;
    float textureScale = 1.0f;
};

