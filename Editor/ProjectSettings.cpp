#include "Panels.h"
#include "scene.h"


void ProjectSettingsPanel::Render(){
    std::string name = "Setting";
    ImGui::Begin(name.c_str());
    static char nameBuffer[128];
    static int currentPresetScene = 0;
    static int currentPresetRes = 2;
    bool fullscreen = (Proj.Param.WindowParam & SDL_WINDOW_FULLSCREEN) != 0;

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;


    if (ImGui::CollapsingHeader("General", flags)) {
        strncpy(nameBuffer, Proj.Param.name.c_str(), sizeof(nameBuffer));
        ImGui::Text("Project Name");
        ImGui::SameLine();
        if (ImGui::InputText("####", nameBuffer, sizeof(nameBuffer))) {
            Proj.Param.name = std::string(nameBuffer);
        }

        ImGui::Text("Starter Scene");
        ImGui::SameLine();

        if (ImGui::Combo("##StarterScene", &currentPresetScene,
                         [](void* data, int idx, const char** out_text) {
                         auto* vec = static_cast<std::vector<scene>*>(data);
                         *out_text = (*vec)[idx].Scenename.c_str();
                         return true;
                         },
                         &Proj.SceneList, Proj.SceneList.size())){
           
            Proj.activeSceneID = Proj.SceneList[currentPresetScene].ID;
        }
        ImGui::Separator();
    }

    if (ImGui::CollapsingHeader("Window", flags)) {
        ImGui::Text("Fullscreen?");
        ImGui::SameLine();
        Uint32 flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
        
        if (ImGui::Checkbox("Fullscreen", &fullscreen)) {
            if (fullscreen) {
                Proj.Param.WindowParam |= SDL_WINDOW_FULLSCREEN; // add fullscreen
            } else {
                Proj.Param.WindowParam &= ~SDL_WINDOW_FULLSCREEN; // remove fullscreen
            }
        }
        ImGui::Separator();
        ImGui::Text("Window Size");
        ImGui::SameLine();
        int size[2] = { Proj.Param.WindowWidth, Proj.Param.WindowHeight };
        if (ImGui::InputInt2("", size)) {

            size[0] = std::max(size[0], 100);
            size[1] = std::max(size[1], 100);

            Proj.Param.WindowWidth  = size[0];
            Proj.Param.WindowHeight = size[1];
        }
        ImGui::Separator();
        ImGui::Text("Resolution");
        ImGui::SameLine();
        if (ImGui::Combo("", &currentPresetRes,[](void* data, int idx, const char** out_text) {
            auto* p = (ResolutionPreset*)data;
            *out_text = p[idx].label;
            return true;
        }, presets, IM_ARRAYSIZE(presets))){
            
            if (currentPresetRes != IM_ARRAYSIZE(presets) - 1) {
                Proj.Param.Resolution.width  = presets[currentPresetRes].w;
                Proj.Param.Resolution.height = presets[currentPresetRes].h;
            }
        }
        if (currentPresetRes == IM_ARRAYSIZE(presets) - 1) {
            ImGui::InputInt("Width",  &Proj.Param.Resolution.width);
            ImGui::InputInt("Height", &Proj.Param.Resolution.height);
        }
        ImGui::Separator();
    }

    ImGui::End();
};

void ProjectSettingsPanel::Update(float dt){}


