#pragma once
#include "components.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "DataTypes/Assets/ScriptAsset.h"
#include "AssetManager.h"
#include "sol/sol.hpp"

class ScriptComponent : public Component {
public:
    AssetHandle scriptHandle; 
    sol::environment env;

    sol::table table;
 
    sol::function onCreate;
    sol::function onUpdate;
    sol::function onDestroy;

    std::string Getname() const override { return "Script"; }

    json Serialize() const override {
        json j;
        j["scriptHandle"] = scriptHandle;
        return j;
    }

    void Deserialize(const json& data) override {
        if (data.contains("scriptHandle"))
        scriptHandle = data["scriptHandle"].get<AssetHandle>();
    }

    void OnRemove(AssetManager& AssetManager) override{}

    void DrawComponentUI(
        AssetManager& assets,
        std::function<GLuint(TextureAsset*)> UploadTextureToGPU,
        std::function<ImTextureID(TextureAsset*)> GetPreviewTextureID){

        std::shared_ptr<ScriptAsset> script = assets.Get<ScriptAsset>(scriptHandle);
 
        ImGui::Text("Script:");

        if (script){
            ImGui::Text("%s", script->Path.c_str());
        }
        else{
            ImGui::TextDisabled("None");
        }

        if (ImGui::Button("Select Script")){
            IGFD::FileDialogConfig config;
            config.path = "/home/abror/Project/GGE/assets/scripts/";

            ImGuiFileDialog::Instance()->OpenDialog(
                "ChooseLuaScript",
                "Choose Lua Script",
                ".lua",
                config
            );
        }

        ImGui::SameLine();

        if (ImGui::Button("New Script")){

            IGFD::FileDialogConfig config;
 
            config.path = "/home/abror/Project/GGE/assets/scripts/";

 
            ImGuiFileDialog::Instance()->OpenDialog(
                "CreateLuaScript",
                "Create Lua Script",
                ".lua",
                config
            );
        }
 
        if (ImGuiFileDialog::Instance()->Display("ChooseLuaScript")){
            if (ImGuiFileDialog::Instance()->IsOk()){
                
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                auto newScript = std::make_shared<ScriptAsset>();

                newScript->Path = filePath;

                AssetHandle handle = assets.RegisterAsset(newScript);
                scriptHandle = handle;
            }
            ImGuiFileDialog::Instance()->Close();
        }
    
        if (ImGuiFileDialog::Instance()->Display("CreateLuaScript")){
            if (ImGuiFileDialog::Instance()->IsOk()){
                std::string path = ImGuiFileDialog::Instance()->GetFilePathName();

                std::ofstream file(path);

file << 
R"(local script = {}
                    
function script.OnCreate(entity)

end

function script.OnUpdate(entity, dt)

end

function script.OnDestroy(entity)

end

return script
)";

                file.close();
 
                auto newScript = std::make_shared<ScriptAsset>();

                newScript->Path = path;

                AssetHandle handle = assets.RegisterAsset(newScript);
                scriptHandle = handle;
            }
            ImGuiFileDialog::Instance()->Close();
        }
    }
};
