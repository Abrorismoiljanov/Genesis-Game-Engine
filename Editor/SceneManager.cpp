#include "Panels.h"

void SceneManagerPanel::Render(){
    if (Proj.SceneList.empty()) {
        scene scene;
        scene.ID = Proj.NextSceneID++;
        scene.Scenename = "Scene" + std::to_string(scene.ID);
        Proj.SceneList.push_back(scene);
    }
    ImGui::Begin( name.c_str());
    
    if (ImGui::Button("+", ImVec2(20, 20))) {
        scene scene;
        scene.ID = Proj.NextSceneID++;
        scene.Scenename = "Scene " + std::to_string(scene.ID);
        Proj.SceneList.push_back(scene);
    }
     
    ImGui::SameLine();
 

    if (Proj.SceneList.size() > 1 && ImGui::Button("X", ImVec2(20, 20))) {
        auto it = std::find_if(Proj.SceneList.begin(), Proj.SceneList.end(),[&](const scene& s){ return s.ID == SelectedScene; });
     
        if (it != Proj.SceneList.end()) {
            Proj.SceneList.erase(it);
            SelectedScene = SIZE_MAX;
        };
    }
    ImGui::Separator();
            
    for (size_t i = 0; i < Proj.SceneList.size(); i++) {

        ImGui::PushID((int)i);
        auto& s = Proj.SceneList[i];
        
        bool selected = (s.ID == SelectedScene);
        if (ImGui::Selectable(s.Scenename.c_str(), selected)) {
            SelectedScene = s.ID;
        }


        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
            int srcIndex = &s - &Proj.SceneList[0]; // index in vector
            ImGui::SetDragDropPayload("SCENE_PAYLOAD", &srcIndex, sizeof(int));
            ImGui::Text("Move %s", s.Scenename.c_str());
            ImGui::EndDragDropSource();
        }

    
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_PAYLOAD")) {
                IM_ASSERT(payload->DataSize == sizeof(int));
                int srcIndex = *(const int*)payload->Data;
                int dstIndex = (int)i;
                if (srcIndex != dstIndex) {
                    auto movedScene = Proj.SceneList[srcIndex];
                    Proj.SceneList.erase(Proj.SceneList.begin() + srcIndex);
                    Proj.SceneList.insert(Proj.SceneList.begin() + dstIndex, movedScene);
                }
            }
            ImGui::EndDragDropTarget();  
        }
        ImGui::PopID();
    }

    ImGui::End();
};
void SceneManagerPanel::Update(float dt){};
