#include "imgui.h"

void ApplyNordTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 4.0f;

    // General
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.2f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.16f, 0.32f, 0.44f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.21f, 0.43f, 0.58f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.31f, 0.53f, 0.68f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.18f, 0.25f, 0.32f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.23f, 0.35f, 0.45f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.28f, 0.42f, 0.55f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.18f, 0.24f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.25f, 0.32f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.23f, 0.32f, 0.42f, 1.0f);

    // Docking / Tabs
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.08f, 0.12f, 0.18f, 1.0f);
    colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.25f, 0.33f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.21f, 0.35f, 0.45f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(0.26f, 0.42f, 0.55f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.12f, 0.18f, 0.25f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.25f, 0.32f, 1.0f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.18f, 0.25f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.18f, 0.25f, 0.32f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.08f, 0.12f, 0.18f, 1.0f);
}

void ApplyCatppuccinMocha() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;

    // Base
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.16f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.25f, 0.22f, 0.36f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.36f, 0.30f, 0.50f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.44f, 0.38f, 0.56f, 1.0f);

    colors[ImGuiCol_Button] = ImVec4(0.30f, 0.25f, 0.44f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.32f, 0.55f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.46f, 0.40f, 0.63f, 1.0f);

    colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.16f, 0.28f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.22f, 0.40f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.34f, 0.28f, 0.50f, 1.0f);

    // Docking / Tabs
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.07f, 0.07f, 0.12f, 1.0f);
    colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.17f, 0.32f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.32f, 0.27f, 0.44f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(0.42f, 0.36f, 0.53f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.13f, 0.25f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.25f, 0.22f, 0.36f, 1.0f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.13f, 0.25f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.22f, 0.36f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.07f, 0.07f, 0.12f, 1.0f);
}

void ApplyGruvboxDark() {
 
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_Text] = ImVec4(0.93f, 0.88f, 0.83f, 1.0f); // light gray / beige
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.6f, 0.55f, 0.51f, 1.0f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.16f, 0.14f, 0.12f, 1.0f); // dark brown
    colors[ImGuiCol_ChildBg]               = ImVec4(0.16f, 0.14f, 0.12f, 1.0f);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.16f, 0.14f, 0.12f, 1.0f);
    colors[ImGuiCol_Border]                = ImVec4(0.24f, 0.18f, 0.14f, 1.0f);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.20f, 0.16f, 0.12f, 1.0f); 
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.24f, 0.20f, 0.16f, 1.0f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.28f, 0.22f, 0.16f, 1.0f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.16f, 0.14f, 0.12f, 1.0f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.24f, 0.18f, 0.14f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.16f, 0.14f, 0.12f, 1.0f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.20f, 0.16f, 0.12f, 1.0f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.16f, 0.14f, 0.12f, 1.0f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.28f, 0.22f, 0.16f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.32f, 0.26f, 0.18f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.36f, 0.30f, 0.20f, 1.0f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.99f, 0.54f, 0.0f, 1.0f); // bright orange
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.99f, 0.54f, 0.0f, 1.0f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.99f, 0.65f, 0.0f, 1.0f);
    colors[ImGuiCol_Button]                = ImVec4(0.24f, 0.18f, 0.14f, 1.0f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.36f, 0.26f, 0.18f, 1.0f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.42f, 0.30f, 0.20f, 1.0f);
    colors[ImGuiCol_Header]                = ImVec4(0.28f, 0.22f, 0.16f, 1.0f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.36f, 0.26f, 0.18f, 1.0f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.42f, 0.30f, 0.20f, 1.0f);
    colors[ImGuiCol_Separator]             = ImVec4(0.24f, 0.18f, 0.14f, 1.0f);
    colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.36f, 0.26f, 0.18f, 1.0f);
    colors[ImGuiCol_SeparatorActive]       = ImVec4(0.42f, 0.30f, 0.20f, 1.0f);
    colors[ImGuiCol_ResizeGrip]            = ImVec4(0.20f, 0.16f, 0.12f, 1.0f);
    colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.36f, 0.26f, 0.18f, 1.0f);
    colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.42f, 0.30f, 0.20f, 1.0f);
    colors[ImGuiCol_PlotLines]             = ImVec4(0.99f, 0.54f, 0.0f, 1.0f);
    colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.99f, 0.65f, 0.0f, 1.0f);
    colors[ImGuiCol_PlotHistogram]         = ImVec4(0.99f, 0.54f, 0.0f, 1.0f);
    colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.99f, 0.65f, 0.0f, 1.0f);
    colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.42f, 0.30f, 0.20f, 1.0f);
    colors[ImGuiCol_DockingPreview]        = ImVec4(0.99f, 0.54f, 0.0f, 0.5f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.16f, 0.14f, 0.12f, 1.0f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.36f, 0.26f, 0.18f, 1.0f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.42f, 0.30f, 0.20f, 1.0f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.16f, 0.14f, 0.12f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.28f, 0.22f, 0.16f, 1.0f);
    colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.16f, 0.14f, 0.12f, 1.0f);
}

void ApplyAyuDark() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;

    colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.12f, 0.15f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.27f, 0.34f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.34f, 0.42f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.33f, 0.43f, 0.52f, 1.0f);

    colors[ImGuiCol_Button] = ImVec4(0.16f, 0.21f, 0.27f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.22f, 0.28f, 0.35f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.28f, 0.36f, 0.44f, 1.0f);

    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.23f, 0.29f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.30f, 0.38f, 1.0f);

    // Docking / Tabs
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.05f, 0.07f, 0.09f, 1.0f);
    colors[ImGuiCol_Tab] = ImVec4(0.17f, 0.21f, 0.26f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.23f, 0.28f, 0.34f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(0.29f, 0.35f, 0.42f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.12f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.23f, 0.29f, 1.0f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.18f, 0.23f, 0.29f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.07f, 0.09f, 1.0f);
}

