#include "Editor/include/Panels.h"
#include "imgui.h"
#include "project.h"
#include "Editor/include/CompRegister.h"
#include "ImGuizmo.h"

void EntityList::Render(){
    ImGui::Begin( name.c_str());
 
    scene* defaultScene = nullptr;

    for (auto& s : Proj.SceneList) {
        if (s.ID == SelectedScene) {
            defaultScene = &s;
            break;
        }
    }

    if (!defaultScene) {
        ImGui::Text("Please select a scene in SceneManager");
        ImGui::End();
        return;
    }

 
    if (defaultScene) {

        ImGui::Text(defaultScene->Scenename.c_str());
        ImGui::Separator();
    
        if (ImGui::Button("+", ImVec2(20, 20))) {
            Proj.AddEntity(defaultScene->ID);
        }
        
        ImGui::SameLine();
    
    
        if (ImGui::Button("X", ImVec2(20, 20))) {
            Proj.DeleteEntity(selection.EntityID);    
        }


        if (defaultScene->EntityIDs.empty()) {
            ImGui::Text("No entities in this scene");
        } else {
            ImGui::BeginChild("ChildID", ImVec2(0, 0), true);
            
            for (size_t i = 0; i < defaultScene->EntityIDs.size(); ++i) {

                uint32_t entityID = defaultScene->EntityIDs[i];
                entity* e = Proj.GetEntityByID(entityID);
 
                if (!e) continue;

      
                ImGui::PushID(entityID);

            
                bool selected = (selection.EntityID == e->ID);
                if (ImGui::Selectable(e->name.c_str(), selected)) {
    
                    selection.ClearEntity();
                
                    selection.EntityID = e->ID;
 
                }

                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                    ImGui::SetDragDropPayload("ENTITY_PAYLOAD", &i, sizeof(size_t));
                    ImGui::Text("Move %s", e->name.c_str());
                    ImGui::EndDragDropSource();
                }

  
                if (ImGui::BeginDragDropTarget()) {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_PAYLOAD")) {
                        ImGui::SameLine();

                        IM_ASSERT(payload->DataSize == sizeof(size_t));
                        size_t srcIndex = *(const size_t*)payload->Data;
 
                        if (srcIndex != i) {
                            auto& ids = defaultScene->EntityIDs;
                            uint32_t movedID = ids[srcIndex];
                            ids.erase(ids.begin() + srcIndex);
                            ids.insert(ids.begin() + i, movedID);
                        }
                    }
                    ImGui::EndDragDropTarget();
                }
                ImGui::PopID();
            }
            ImGui::EndChild();
        }
    }
     ImGui::End();
}

void EntityList::Update(float dt){};

void Inspector::Render(){

    entity* CurrentEntity = nullptr;
    uint32_t selectedID = selection.EntityID;

    for (auto& SelectedE : Proj.EntityList) {
        if (selection.EntityID == SelectedE.ID) {
            CurrentEntity = &SelectedE;
        }
    } 

    ImGui::Begin(name.c_str());
    
    if (!CurrentEntity) {
        ImGui::Text("No Entity Selected");
    }


    if (CurrentEntity != nullptr) {

        CurrentEntity->DrawInfoUI();

        auto& comps = CurrentEntity->ComponentIDs;

        uint32_t componentToDelete = 0;
        bool hasDeleteRequest = false;

        for (size_t i = 0; i < comps.size(); ++i) {    
            uint32_t compID = comps[i];
 
            if (Component* c = Proj.GetComponentByID(compID)) {
                ImGui::PushID(compID);
                ImGui::Dummy(ImVec2(1, 1));
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
                
                float totalButtonWidth = 80.0f; 
                float spacing = 4.0f;
                float posX = ImGui::GetWindowContentRegionMax().x - totalButtonWidth - spacing;
                ImGui::SameLine(posX);

                bool requestDelete = false;

                if (ImGui::Button(ICON_FA_TRASH)) {
                    hasDeleteRequest = true;
                    componentToDelete = compID;
                        c->OnRemove(Proj.Assets);
                }

                ImGui::SameLine(0, 5.0f);

                if (ImGui::ArrowButton("##up", ImGuiDir_Up) && i > 0) {
                    std::swap(comps[i], comps[i - 1]);
                }

                ImGui::SameLine(0, 5.0f);

                if (ImGui::ArrowButton("##down", ImGuiDir_Down) && i + 1 < comps.size()) {
                    std::swap(comps[i], comps[i + 1]);
                }
                bool open = ImGui::CollapsingHeader(c->Getname().c_str(), flags);
 
                if (open) {
                    c->DrawComponentUI(Proj.Assets, std::bind(&Renderer::UploadTextureToGPU, m_renderer, std::placeholders::_1),
                                       std::bind(&Renderer::GetPreviewTextureID, m_renderer, std::placeholders::_1));
                }
           
                ImGui::PopID();
            }
        }

        if (hasDeleteRequest) {
            Proj.DeleteComponent(componentToDelete);
        }
        
        ImGui::Spacing(); 
        float width = ImGui::GetContentRegionAvail().x;
        if (ImGui::Button("Add Component", ImVec2(width, 0))) {

            ImGui::OpenPopup("ComponentSelectionPopup");
        }
        ImGui::SetNextWindowSizeConstraints(
            ImVec2(240, 0),     
            ImVec2(360, FLT_MAX) 
            );

        ImGui::PushStyleColor(ImGuiCol_PopupBg,    ImVec4(0.12f, 0.13f, 0.17f, 0.98f));  
        ImGui::PushStyleColor(ImGuiCol_Border,     ImVec4(0.28f, 0.56f, 1.00f, 0.60f));  
        ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, 1.8f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 6.0f);                       
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,   ImVec2(10.0f, 10.0f));         

        if (ImGui::BeginPopup("ComponentSelectionPopup")){

            uint32_t entityId = selection.EntityID;
            float avail_width = ImGui::GetContentRegionAvail().x;

            for (const auto& desc : ComponentRegistry::Get().All()){
                bool alreadyHas = desc.has(Proj, entityId);
                bool canAdd = desc.allowDupe || !alreadyHas;
                ImGui::BeginDisabled(!canAdd);
                if (ImGui::Button(desc.name.c_str(), ImVec2(avail_width, 0))){
                    if (canAdd){
                        desc.add(Proj, entityId);
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::EndDisabled();
                if (!canAdd && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)){
                    ImGui::SetTooltip("%s is already attached (duplicates not allowed)", desc.name.c_str());
                }
            }
     
            ImGui::EndPopup();
        }   
        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar(3);

    }
 
    ImGui::End();   
};
    
void Inspector::Update(float dt){};


