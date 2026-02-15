#pragma once
#include "Asset.h"
#include "glm/glm.hpp"
#include <string>

class MaterialAsset : public Asset {
public:
    MaterialAsset(const std::string& name) : Name(name) {}

    std::string Name;

    glm::vec4 DiffuseColor = glm::vec4(1.0f); 
    glm::vec4 SpecularColor = glm::vec4(1.0f);
    float Shininess = 32.0f; 

    void Bind() const {}
};
