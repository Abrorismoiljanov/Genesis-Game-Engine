#include "Panels.h"


void ProjectSettingsPanel::Render(){
    std::string name = "Setting";
    ImGui::Begin(name.c_str());
    static char nameBuffer[128];
    static int currentPreset = 1;
    bool fullscreen = (Proj.Param.WindowParam & SDL_WINDOW_FULLSCREEN) != 0;


    if (ImGui::CollapsingHeader("General")) {
        strncpy(nameBuffer, Proj.Param.name.c_str(), sizeof(nameBuffer));
        ImGui::Text("Project Name");
        ImGui::SameLine();

        if (ImGui::InputText("####", nameBuffer, sizeof(nameBuffer))) {
            Proj.Param.name = std::string(nameBuffer);
        }
        ImGui::Separator();
    }

    if (ImGui::CollapsingHeader("Window")) {
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
        if (ImGui::Combo("", &currentPreset,[](void* data, int idx, const char** out_text) {
            auto* p = (ResolutionPreset*)data;
            *out_text = p[idx].label;
            return true;
        }, presets, IM_ARRAYSIZE(presets))){
            
            if (currentPreset != IM_ARRAYSIZE(presets) - 1) {
                Proj.Param.Resolution.width  = presets[currentPreset].w;
                Proj.Param.Resolution.height = presets[currentPreset].h;
            }
        }
        if (currentPreset == IM_ARRAYSIZE(presets) - 1) {
            ImGui::InputInt("Width",  &Proj.Param.Resolution.width);
            ImGui::InputInt("Height", &Proj.Param.Resolution.height);
        }
        ImGui::Separator();
    }

    ImGui::End();
};

void ProjectSettingsPanel::Update(float dt){}


