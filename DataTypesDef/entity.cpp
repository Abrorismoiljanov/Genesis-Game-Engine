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
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::Separator();
    };
    ImGui::Dummy(ImVec2(1, 1));
};
