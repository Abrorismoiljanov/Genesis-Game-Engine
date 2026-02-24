#include "entity.h"
#include "imgui.h"

void entity::DrawInfoUI(){                     
    char buffer[128];  
    strncpy(buffer, name.c_str(), sizeof(buffer));
    buffer[sizeof(buffer)-1] = '\0'; // ensure null-termination

    if (name == "") {
        name = "Entity " + std::to_string(ID);
    }

    ImGui::Dummy(ImVec2(0.0f, 2.0f));
    if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen)){
         ImGui::Text("name");
        ImGui::SameLine();
        if(ImGui::InputText("####", buffer, sizeof(buffer))){
            name = buffer;
        }
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


        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::Separator();
    };
    ImGui::Dummy(ImVec2(1, 1));
};
