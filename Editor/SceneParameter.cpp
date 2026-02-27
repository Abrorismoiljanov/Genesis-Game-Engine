#include "Panels.h"

void SceneParamPanel::Render(){

    scene* defaultScene = nullptr;

    for (auto& s : Proj.SceneList) {
        if (s.ID == SelectedScene) {
            defaultScene = &s;
        }
    }
    char buffer[128];  
    strncpy(buffer, defaultScene->Scenename.c_str(), sizeof(buffer));
    buffer[sizeof(buffer)-1] = '\0'; // ensure null-termination

    ImGui::Begin("Scene Parameter");
   if (defaultScene != nullptr) {
    ImGui::Text(defaultScene->Scenename.c_str());
   }
    ImGui::Separator();      
    ImGui::Text("Scene Name");
    ImGui::SameLine();
    float w = ImGui::GetContentRegionAvail().x;    
 
        
    ImGui::PushItemWidth(w);
    if(ImGui::InputText("####", buffer, sizeof(buffer))){
        defaultScene->Scenename = buffer;
    }

    ImGui::PopItemWidth();
    ImGui::Separator();

    ImGui::Text("Background Color");
    ImGui::SameLine();
    ImGui::ColorEdit4("", glm::value_ptr(defaultScene->Param.BackgroundColor), ImGuiColorEditFlags_DisplayRGB |
                      ImGuiColorEditFlags_AlphaBar |
                      ImGuiColorEditFlags_NoInputs);
    ImGui::End();
};

void SceneParamPanel::Update(float dt){};
