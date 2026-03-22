#include "Editor/include/Panels.h"

void Terminal::Render(){
    ImGui::Begin("Terminal");

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
 
    if (ImGui::Button("Clear")){
        Log->Clear();
    };
    ImGui::SameLine();

    if(ImGui::InputFloat("###Font", &fontSize)){
        myFont = io.Fonts->AddFontFromFileTTF(
        "/home/abror/Project/GGE/assets/fonts/JetBrainsMono-2.304/fonts/ttf/JetBrainsMono-Medium.ttf",
        fontSize
    );
    }
        
    ImGui::PopStyleVar();
    ImGui::Separator();


    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));

    ImGui::BeginChild("LogRegion", ImVec2(0, 0), true); 
    std::vector<LogEntry> logs = Log->GetSnapshot();
    ImGui::PushFont(myFont);


    for (auto& l : logs) {

        ImVec4 colorMessage;
        ImVec4 colorSystem;
        switch (l.level) {
            case LogLevel::Info:    colorMessage = ImVec4(0.0f, 0.8f, 0.9f, 1.0f); break;      
            case LogLevel::Warning: colorMessage = ImVec4(1.0f, 0.9f, 0.3f, 1.0f); break;     
            case LogLevel::Error:   colorMessage = ImVec4(1.0f, 0.2f, 0.2f, 1.0f); break;     
        }
        switch (l.system) {
            case LogSystem::Script:   colorSystem = ImVec4(0.0f, 1.0f, 0.5f, 1.0f); break;  
            case LogSystem::Physics:  colorSystem = ImVec4(0.2f, 0.6f, 1.0f, 1.0f); break;  
            case LogSystem::Renderer: colorSystem = ImVec4(1.0f, 0.5f, 0.0f, 1.0f); break;   
            case LogSystem::Engine:   colorSystem = ImVec4(1.0f, 0.0f, 1.0f, 1.0f); break;   
            case LogSystem::Gameplay: colorSystem = ImVec4(1.0f, 0.8f, 0.0f, 1.0f); break;   
        }

        ImGui::TextColored(colorSystem, "[%s]",Log->LogSystemToString(l.system));
        ImGui::SameLine();
        ImGui::TextColored(colorMessage, "%s", l.message.c_str());

    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);


    ImGui::PopFont();
    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::End();
}
void Terminal::Update(float dt){};


