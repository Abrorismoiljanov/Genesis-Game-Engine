#pragma once
#include <cstdint>
#include <string>

class AssetManager;

class Component {
public:
    uint32_t ID;        
    uint32_t OwnerEntityID;
    virtual ~Component() = 0;
    virtual std::string Getname() = 0;


    virtual void DrawComponentUI(AssetManager& AssetManager) = 0;
};

