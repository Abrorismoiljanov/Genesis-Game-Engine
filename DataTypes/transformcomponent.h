#pragma once

#include "glm/glm.hpp"
#include "components.h"
#include "imgui.h"
#include "project.h"

struct TransformData{
    glm::vec3 position {0.0f};
    glm::vec3 rotation {0.0f}; 
    glm::vec3 scale    {1.0f};
};


class TransformComponent: public Component{
public:
    TransformData transform;

    std::string Getname(){
        return "Transform";
    }

    void DrawComponentUI(){

    ImGui::Dummy(ImVec2(0.0f, 2.0f));

        float w = ImGui::GetContentRegionAvail().x / 4.0f;    
 
        ImGui::PushItemWidth(w);
        ImGui::Text("Location");
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::DragFloat("###1", &transform.position.x, 0.1);
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::DragFloat("###2", &transform.position.y, 0.1);
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::DragFloat("###3", &transform.position.z, 0.1);
        ImGui::PopItemWidth();
        
        ImGui::PushItemWidth(w);
        ImGui::Text("Rotation");
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::DragFloat("###4", &transform.rotation.x, 1.0f);
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::DragFloat("###5", &transform.rotation.y, 1);
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::DragFloat("###6", &transform.rotation.z, 1);
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
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::DragFloat("###9", &transform.scale.z, 0.1);
        ImGui::PopItemWidth();    
        ImGui::Dummy(ImVec2(0.0f, 10.0f));   
        ImGui::Separator();
    };
};


