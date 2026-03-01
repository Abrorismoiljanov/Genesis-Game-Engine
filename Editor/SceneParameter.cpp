#include "Panels.h"

void SceneParamPanel::Render(){

    scene* defaultScene = Proj.GetSceneByID(SelectedScene);

    bool ValidScene = (defaultScene != nullptr);

    ImGui::Begin("Scene Parameter");
    if (!ValidScene) {
        ImGui::Text("Please Select a Scene");
    }
 
    if (ValidScene) {
        char buffer[128];  
        strncpy(buffer, defaultScene->Scenename.c_str(), sizeof(buffer));
        buffer[sizeof(buffer)-1] = '\0';

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
    }
    ImGui::End();
};

void SceneParamPanel::Update(float dt){};
