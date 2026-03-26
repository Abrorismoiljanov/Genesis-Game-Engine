#include "Editor/include/Panels.h"
#include "DataTypes/entity.h"

void SceneParamPanel::Render(){

    scene* defaultScene = Proj.GetSceneByID(SelectedScene);
    bool ValidScene = (defaultScene != nullptr);
 
    int currentIndex = -1;
    int comboIndex = 0;
    const char* previewName = "None";

    ImGui::Begin("Scene Parameter");
    if (!ValidScene) {
        ImGui::Text("Please Select a Scene");
        ImGui::End();
        return;
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

    ImGui::Text("Active Camera");
    ImGui::SameLine();
    if (defaultScene->Camera != -1) {
        entity* camEntity = Proj.GetEntityByID(defaultScene->Camera);
        
        bool camValid = false;
        if (camEntity) {
            for (auto& cID : camEntity->ComponentIDs) {
                auto* c = Proj.GetComponentByID(cID);
                if (c && c->Getname() == "Camera") {
                    camValid = true;
                    break;
                }
            }
        }
        if (!camValid) {
            defaultScene->Camera = -1;
            previewName = "None";
        } else {
            previewName = camEntity->name.c_str();
        }
    }
    if (ImGui::BeginCombo("##", previewName)) {
        for (auto& eID: defaultScene->EntityIDs) {
            entity* Entity = Proj.GetEntityByID(eID);
            bool hasCamera = false;
            if (!Entity) continue;

            for (auto& cID: Entity->ComponentIDs) {
                auto* c = Proj.GetComponentByID(cID);
                if (!c) continue;
                if (c->Getname() == "Camera") {
                    hasCamera = true;
                }
            }
            if (!hasCamera) continue;
      
            bool isSelected = (defaultScene->Camera == Entity->ID);

            if (ImGui::Selectable(Entity->name.c_str(), isSelected)){
                defaultScene->Camera = Entity->ID;
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

ImGui::End();
};

void SceneParamPanel::Update(float dt){};
