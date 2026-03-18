#include "Editor/include/Panels.h"

void Terminal::Render(){
    ImGui::Begin("Terminal");
    for (auto& l : Log->Get()) {
        ImVec4 color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
        if (l.level == LogLevel::Warning) color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        else if (l.level == LogLevel::Error) color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

        ImGui::TextColored(color, "[%s] %s",
            Log->LogSystemToString(l.system),
            l.message.c_str());
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::End();
}
void Terminal::Update(float dt){};


