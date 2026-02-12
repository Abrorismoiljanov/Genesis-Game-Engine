#pragma once
#include "components.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include "ImGuiFileDialog.h"

#include "Assets/MaterialAsset.h"
#include "transformcomponent.h"
#include "Assets/MeshAsset.h"

class MeshComponent: public Component{
public:

    std::vector<Mesh> meshes;
   TransformData transform;
    std::string MeshPath;


    std::string Getname(){
        return "Mesh";
    };

    void DrawComponentUI(){

        if (ImGui::Button("Load Mesh", ImVec2(0,30))) {
            IGFD::FileDialogConfig cfg;

            ImGuiFileDialog::Instance()->OpenDialog(
                "Choosef",
                "Choose File",
                ".obj,.glb,.gltf",
                cfg
            );
        }
        ImGui::SameLine();


        if (ImGuiFileDialog::Instance()->Display("Choosef"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
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
