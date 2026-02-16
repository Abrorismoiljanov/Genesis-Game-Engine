#pragma once
#include "components.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include "ImGuiFileDialog.h"
#include "GL/glew.h"

#include "transformcomponent.h"
#include "Assets/ModelAsset.h"
#include "Assets/MaterialAsset.h"

class MeshComponent: public Component{
private:
    std::string _LastLoadedPath;
public:
    AssetHandle HandleMesh;
    TransformData transform;
    std::vector<AssetHandle> HandleMaterials;
    
    bool Loaded = false;
    std::string MeshPath;

   bool MatNeedsLoad() const { return !Loaded; }
    void MatMarkLoaded() { Loaded = true; }

    std::string Getname(){
        return "Mesh";
    };

    bool NeedsLoad() const {
        return !MeshPath.empty() && MeshPath != _LastLoadedPath;
    }

    void MarkLoaded() {
        _LastLoadedPath = MeshPath;
    }
    
glm::mat4 GetMatrix() const {
    glm::mat4 T = glm::translate(glm::mat4(1.0f), transform.position);

    glm::mat4 Rx = glm::rotate(glm::mat4(1.0f),
                               glm::radians(transform.rotation.x),
                               glm::vec3(1,0,0));
    glm::mat4 Ry = glm::rotate(glm::mat4(1.0f),
                               glm::radians(transform.rotation.y),
                               glm::vec3(0,1,0));
    glm::mat4 Rz = glm::rotate(glm::mat4(1.0f),
                               glm::radians(transform.rotation.z),
                               glm::vec3(0,0,1));

    glm::mat4 S = glm::scale(glm::mat4(1.0f), transform.scale);

    return T * Rz * Ry * Rx * S;
}

    void DrawComponentUI(){
        std::string btnID = "Load Mesh##" + std::to_string(ID);
        if (ImGui::Button(btnID.c_str(), ImVec2(0,30))) {
            IGFD::FileDialogConfig cfg;

            ImGuiFileDialog::Instance()->OpenDialog(
                ("Choosef##" + std::to_string(ID)).c_str(),
                "Choose File",
                ".glb,.fbx,.obj,.gltf",
                cfg
            );
        }
        ImGui::SameLine();

        std::string dlgID = "Choosef##" + std::to_string(ID);
        if (ImGuiFileDialog::Instance()->Display(dlgID.c_str(), ImGuiWindowFlags_NoCollapse, ImVec2(800, 600))){
            if (ImGuiFileDialog::Instance()->IsOk()){
                MeshPath = ImGuiFileDialog::Instance()->GetFilePathName();
            }
            ImGuiFileDialog::Instance()->Close();
        }
        ImGui::BeginChild("MeshPathBox", ImVec2(0, 30), true); // true = frame 
        ImGui::Text("%s", MeshPath.c_str());
        ImGui::EndChild();

        ImGui::Separator();
    }

private:
    static uint32_t s_NextID;

    static uint32_t GenerateUniqueID() {
        return ++s_NextID;
    }
};
