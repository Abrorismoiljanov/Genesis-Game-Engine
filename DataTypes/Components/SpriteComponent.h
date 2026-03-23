#pragma once
#include "components.h"
#include "Assets/Asset.h"
#include "DataTypes/Assets/MaterialAsset.h"
#include "imgui.h"
#include "AssetManager.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "glm/glm.hpp"

struct SpriteComponent : public Component {
    AssetHandle materialHandle = INVALID_ASSET;
    glm::vec2 size = {1.0f, 1.0f};       
    glm::vec2 offset = {0.0f, 0.0f};    
    IGFD::FileDialogConfig cfg;


    std::string Getname() const override{
        return "Sprite";
    };

json Serialize() const override {
        json j;
        j["materialHandle"] = materialHandle;
        j["size"]           = {size.x, size.y};
        j["offset"]         = {offset.x, offset.y};
        return j;
    }

    void Deserialize(const json& data) override {
        materialHandle = INVALID_ASSET;
        size = {1.0f, 1.0f};

        if (data.contains("materialHandle")) {
            materialHandle = data["materialHandle"].get<AssetHandle>();
        }

        if (data.contains("size") && data["size"].is_array() && data["size"].size() == 2) {
            size.x = data["size"][0].get<float>();
            size.y = data["size"][1].get<float>();
        }
        if (data.contains("offset") && data["offset"].is_array() && data["offset"].size() == 2) {
            offset.x = data["offset"][0].get<float>();
            offset.y = data["offset"][1].get<float>();
        }
    };

    void OnRemove(AssetManager& assetManager){
        auto mat = assetManager.Get<MaterialAsset>(materialHandle);
        std::shared_ptr<TextureAsset> tex;
        tex = mat->GetTexture();
        assetManager.DeleteAsset(tex->Handle);
        assetManager.DeleteAsset(materialHandle);
    };


   void DrawComponentUI(AssetManager& assetManager,  
                        std::function<GLuint(TextureAsset*)> UploadTextureToGPU,
                        std::function<ImTextureID(TextureAsset*)> GetPreviewTextureID){
 
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
        ImGui::DragFloat2("Offset", &offset.x, 0.1f);

        std::string btnID = "Load Material##" + std::to_string(ID);
        if (ImGui::Button(btnID.c_str(), ImVec2(0,30))) {
 
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
              
                if (UploadTextureToGPU) {
                    UploadTextureToGPU(tex.get());
                }

                size = {tex->Width, tex->Height};
            }
            ImGuiFileDialog::Instance()->Close();
        }
   
        ImGui::BeginChild("TexturePathBox", ImVec2(0, 150), true); // true = frame 
        if(tex && GetPreviewTextureID) {
            ImTextureID previewID = GetPreviewTextureID(tex.get());
            if (previewID) {
                ImVec2 maxSize(128, 128); 
                float texWidth  = (float)tex->Width;  
                float texHeight = (float)tex->Height;

                float scale = std::min(maxSize.x / texWidth, maxSize.y / texHeight);

                ImVec2 previewSize(texWidth * scale, texHeight * scale);
                ImGui::Image(previewID, previewSize, ImVec2(0,0), ImVec2(1,1));
            }
        }
        ImGui::EndChild();

        ImGui::Separator();
    }
};
