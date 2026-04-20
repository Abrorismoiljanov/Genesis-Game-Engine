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

    style.WindowRounding = 4.0f;
    style.FrameRounding = 2.0f;

    colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.05f, 0.03f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.35f, 0.22f, 0.14f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.29f, 0.18f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.55f, 0.36f, 0.25f, 1.0f);

    colors[ImGuiCol_Button] = ImVec4(0.25f, 0.15f, 0.09f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.22f, 0.14f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.29f, 0.18f, 1.0f);

    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.07f, 0.03f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.12f, 0.06f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.32f, 0.18f, 0.09f, 1.0f);

    // Docking / Tabs
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.05f, 0.03f, 0.01f, 1.0f);
    colors[ImGuiCol_Tab] = ImVec4(0.30f, 0.18f, 0.10f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.25f, 0.14f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(0.50f, 0.33f, 0.20f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.12f, 0.06f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.28f, 0.16f, 0.08f, 1.0f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.12f, 0.06f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.35f, 0.22f, 0.14f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.03f, 0.01f, 1.0f);
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

