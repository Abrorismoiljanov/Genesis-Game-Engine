#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "components.h"
#include "imgui.h"
#include "project.h"



class TransformComponent: public Component{
public:
    TransformData transform;

    std::string Getname()const override{
        return "Transform";
    }

    json Serialize() const override {
        json j;
        j["position"] = { transform.position.x, transform.position.y, transform.position.z };
        j["rotation"] = transform.rotation;
        j["scale"]    = { transform.scale.x,    transform.scale.y,    transform.scale.z };
        return j;
    }

    void Deserialize(const json& data) override {
        // Safe defaults
        transform.position = {0.0f, 0.0f, 0.0f};
        transform.rotation = 0.0f;
        transform.scale    = {1.0f, 1.0f, 1.0f};

        // position
        if (data.contains("position") && data["position"].is_array() && data["position"].size() == 3) {
            transform.position.x = data["position"][0].get<float>();
            transform.position.y = data["position"][1].get<float>();
            transform.position.z = data["position"][2].get<float>();
        }

        // rotation
        if (data.contains("rotation")) {
            transform.rotation = data["rotation"].get<float>();
        }

        // scale
        if (data.contains("scale") && data["scale"].is_array() && data["scale"].size() == 3) {
            transform.scale.x = data["scale"][0].get<float>();
            transform.scale.y = data["scale"][1].get<float>();
            transform.scale.z = data["scale"][2].get<float>();
        }
    }

    void DrawComponentUI(AssetManager& AssetManager){

    ImGui::Dummy(ImVec2(0.0f, 2.0f));

        float w = ImGui::GetContentRegionAvail().x / 2.5f;    
 
        ImGui::PushItemWidth(w);
        ImGui::Text("Location");
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::DragFloat("###1", &transform.position.x, 0.1);
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::DragFloat("###2", &transform.position.y, 0.1);
        ImGui::PopItemWidth();
        
        ImGui::PushItemWidth(w);
        ImGui::Text("Rotation");

        ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::DragFloat("###6", &transform.rotation, 1);
        ImGui::PopItemWidth();
   
        ImGui::PushItemWidth(w);
        ImGui::Text("Scale");
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::DragFloat("###7", &transform.scale.x, 0.1);
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::DragFloat("###8", &transform.scale.y, 0.1);
        ImGui::PopItemWidth();
        ImGui::Separator();
    };
};


