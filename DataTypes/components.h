#pragma once
#include <cstdint>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class AssetManager;

class Component {
public:
    uint32_t ID;        
    uint32_t OwnerEntityID;
    virtual ~Component() = 0;
    virtual std::string Getname() const = 0;

    virtual void DrawComponentUI(AssetManager& AssetManager) = 0;
    virtual json Serialize() const = 0;
    virtual void Deserialize(const json& data) = 0;
};

