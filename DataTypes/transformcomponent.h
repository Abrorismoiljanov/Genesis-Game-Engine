#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "components.h"
#include "imgui.h"
#include "project.h"


struct TransformData{
    glm::vec3 position {0.0f};
    float rotation {0.0f}; 
    glm::vec3 scale    {1.0f};
};


class TransformComponent: public Component{
public:
    TransformData transform;

    std::string Getname(){
        return "Transform";
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


