#pragma once
#include "Components/components.h"
#include "glm/glm.hpp"

class CollisionComponent : public Component {
public:    
    glm::vec3 offset = {0.0f, 0.0f, 0.0f};   
    glm::vec3 halfSize = {0.5f, 0.5f, 0.0f};

    bool isTrigger = false;
    bool isStatic  = false;

    uint32_t layer = 1;
    uint32_t mask  = 1;

    std::string Getname() const override {
        return "Collision";
    }

    sol::object PushToLua(sol::state_view lua) {
        return sol::make_object(lua, this);
    }

    void OnRemove(AssetManager &AssetManager) override{

    }

    void DrawComponentUI(AssetManager &AssetManager, 
                         std::function<GLuint (TextureAsset *)> UploadTextureToGPU, 
                         std::function<ImTextureID (TextureAsset *)> GetPreviewTextureID) override{
    

        ImGui::Text("Current Offset: x=%.2f, y=%.2f, z=%.2f", offset.x, offset.y, offset.z);
        ImGui::DragFloat3("Offset", &offset.x, 0.1f);

        ImGui::DragFloat3("Half Size", &halfSize.x, 0.1f);
        ImGui::Text("Current HalfSize: x=%.2f, y=%.2f, z=%.2f", halfSize.x, halfSize.y, halfSize.z);

        ImGui::Checkbox("Is Trigger", &isTrigger);
        ImGui::Checkbox("Is Static", &isStatic);

        ImGui::InputInt("Layer", (int*)&layer);
        ImGui::InputInt("Mask", (int*)&mask);
    }


    json Serialize() const override {
        json j;
        j["offset"]   = {offset.x, offset.y};
        j["halfSize"] = {halfSize.x, halfSize.y};
        j["isTrigger"] = isTrigger;
        j["isStatic"]  = isStatic;
        j["layer"]     = layer;
        j["mask"]      = mask;
        return j;
    }

    void Deserialize(const json& data) override {
        if (data.contains("offset")) {
            offset.x = data["offset"][0];
            offset.y = data["offset"][1];
        }

        if (data.contains("halfSize")) {
            halfSize.x = data["halfSize"][0];
            halfSize.y = data["halfSize"][1];
        }

        if (data.contains("isTrigger")) isTrigger = data["isTrigger"];
        if (data.contains("isStatic"))  isStatic  = data["isStatic"];
        if (data.contains("layer"))     layer     = data["layer"];
        if (data.contains("mask"))      mask      = data["mask"];
    }

};
