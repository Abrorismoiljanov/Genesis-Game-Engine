#include "Editor/include/Panels.h"

void Terminal::Render(){
    ImGui::Begin("Terminal");

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
 
    if (ImGui::Button("Clear")){
        Log->Clear();
    };

    ImGui::PopStyleVar();
    ImGui::Separator();


    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));

    ImGui::BeginChild("LogRegion", ImVec2(0, 0), true); 
    std::vector<LogEntry> logs = Log->GetSnapshot();
    ImGui::PushFont(myFont);


    for (auto& l : logs) {

        ImVec4 color;
        ImVec4 colorType;
        switch (l.level) {
            case LogLevel::Info:    color = ImVec4(1,1,1,1); break;
            case LogLevel::Warning: color = ImVec4(1,1,0,1); break;
            case LogLevel::Error:   color = ImVec4(1,0.3f,0.3f,1); break;
        }
        switch (l.system) {
            case LogSystem::Engine : colorType = ImVec4(1,1,0,1); break;
            case LogSystem::Renderer : colorType = ImVec4(0,1,1,1); break;
            case LogSystem::Script : colorType = ImVec4(0,1,0,1); break;
        }

        ImGui::TextColored(colorType, "[%s]",Log->LogSystemToString(l.system));
        ImGui::SameLine();
        ImGui::TextColored(color, "%s", l.message.c_str());

    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);


    ImGui::PopFont();
    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::End();
}
void Terminal::Update(float dt){};


