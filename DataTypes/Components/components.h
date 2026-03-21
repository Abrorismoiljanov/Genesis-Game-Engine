#pragma once
#include <cstdint>
#include <string>
#include "nlohmann/json.hpp"
#include "GL/glew.h"
#include "DataTypes/Assets/TextureAsset.h"
#include "imgui.h"
#include "sol/sol.hpp"

using json = nlohmann::json;

class AssetManager;
//Later use
enum ComponentType{
    none,
    Sprite,
    Camera
};

class Component {
public:
    uint32_t ID;        
    uint32_t OwnerEntityID;

    virtual ~Component() = 0;
    virtual std::string Getname() const = 0;

    virtual void DrawComponentUI(AssetManager& AssetManager,
                                 std::function<GLuint(TextureAsset*)> UploadTextureToGPU,
                                 std::function<ImTextureID(TextureAsset*)> GetPreviewTextureID) = 0;

    virtual sol::object PushToLua(sol::state_view lua) {
        return sol::nil;
    }

    virtual json Serialize() const = 0;
    virtual void Deserialize(const json& data) = 0;
    virtual void OnRemove(AssetManager& AssetManager) = 0;
};

