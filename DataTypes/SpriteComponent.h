#pragma once
#include "components.h"
#include "Assets/Asset.h"
#include "Assets/MaterialAsset.h"
#include "imgui.h"
#include "AssetManager.h"
#include "ImGuiFileDialog.h"
#include "glm/glm.hpp"

struct SpriteComponent : public Component {
    AssetHandle materialHandle = INVALID_ASSET; // reference to a MaterialAsset
    glm::vec2 size = {1.0f, 1.0f};              // width/height
    float rotation = 0.0f;                      // rotation in degrees

    std::string Getname() const override{
        return "Sprite";
    };

json Serialize() const override {
        json j;
        j["materialHandle"] = materialHandle;
        j["size"]           = {size.x, size.y};
        j["rotation"]       = rotation;
        return j;
    }

    void Deserialize(const json& data) override {
        materialHandle = INVALID_ASSET;
        size = {1.0f, 1.0f};
        rotation = 0.0f;

        if (data.contains("materialHandle")) {
            materialHandle = data["materialHandle"].get<AssetHandle>();
        }

        if (data.contains("size") && data["size"].is_array() && data["size"].size() == 2) {
            size.x = data["size"][0].get<float>();
            size.y = data["size"][1].get<float>();
        }

        if (data.contains("rotation")) {
            rotation = data["rotation"].get<float>();
        }
    };

    void OnRemove(AssetManager& assetManager){
        auto mat = assetManager.Get<MaterialAsset>(materialHandle);
        std::shared_ptr<TextureAsset> tex;
        tex = mat->GetTexture();
        assetManager.DeleteAsset(tex->Handle);
        assetManager.DeleteAsset(materialHandle);
    };

   void DrawComponentUI(AssetManager& assetManager){
 
        auto mat = assetManager.Get<MaterialAsset>(materialHandle);
        std::string path = mat && mat->GetTexture() ? mat->GetTexture()->Path : "None";
 
        std::shared_ptr<TextureAsset> tex;
        if(mat) {
            tex = mat->GetTexture();
        }
 
        std::string tpath = tex ? tex->Path : "None";
        ImGui::Text("Material: %s", path.c_str());
 


        if(!mat) {
            auto newMat = std::make_shared<MaterialAsset>();
            auto newTex = std::make_shared<TextureAsset>();
            newMat->SetTexture(newTex);
            materialHandle = assetManager.RegisterAsset(newMat);
            mat = newMat;
            tex = newTex;
            tex->Type = AssetType::Texture;
        }

        ImGui::DragFloat2("Size", &size.x, 0.1f);

        std::string btnID = "Load Material##" + std::to_string(ID);
        if (ImGui::Button(btnID.c_str(), ImVec2(0,30))) {
            IGFD::FileDialogConfig cfg;

            ImGuiFileDialog::Instance()->OpenDialog(
                ("Choosef##" + std::to_string(ID)).c_str(),
                "Choose File",
                ".png,.jpeg,.jpg,.bmp",
                cfg
            );
        }
        ImGui::SameLine();

        std::string dlgID = "Choosef##" + std::to_string(ID);
        if (ImGuiFileDialog::Instance()->Display(dlgID.c_str(), ImGuiWindowFlags_NoCollapse, ImVec2(800, 600))){
            if (ImGuiFileDialog::Instance()->IsOk()){
                path = ImGuiFileDialog::Instance()->GetFilePathName();
                mat->GetTexture()->LoadFromFile(path);
                mat->GetTexture()->UploadToGPU();
                size = {tex->Width, tex->Height};
            }
            ImGuiFileDialog::Instance()->Close();
        }
   
        ImGui::BeginChild("MeshPathBox", ImVec2(0, 150), true); // true = frame 
        if(tex && tex->ID) {
        
        ImVec2 maxSize(128, 128); 
        float texWidth  = (float)tex->Width;  
        float texHeight = (float)tex->Height;

        float scale = std::min(maxSize.x / texWidth, maxSize.y / texHeight);

            ImVec2 previewSize(texWidth * scale, texHeight * scale);
            ImGui::Image((ImTextureID)(uintptr_t)tex->ID, previewSize, ImVec2(0,1), ImVec2(1,0));
        }
        ImGui::EndChild();

        ImGui::Separator();
    }


};
