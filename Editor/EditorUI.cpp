#include "EditorUI.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "SDL2/SDL.h"
#include "ComponentRegisterList.h"
#include "ImGuiFileDialog.h"

EditorUI::EditorUI(project& proj): Project(proj), renderer(nullptr){}

void EditorUI::Init(SDL_Window* window, SDL_GLContext glContext, project& Proj, Renderer* renderer){

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Optional style tweaks
    ImGui::StyleColorsDark();
    ImGui::GetStyle().WindowRounding = 6.0f;
    ImGui::GetStyle().FrameRounding = 4.0f;

    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");

    RegisterAllComponents();
    panels.push_back(std::make_unique<TestPanel>("Panel 1"));
    panels.push_back(std::make_unique<EntityList>("Scene List", Proj, Selection));
    panels.push_back(std::make_unique<Inspector>("Inspector", Proj, Selection));
    panels.push_back(std::make_unique<Viewport>("Viewport", Proj, Selection, renderer));

};

void EditorUI::Update(float deltaTime){
    for (auto& panel : panels) {
        panel->Update(deltaTime);
    }
};

void EditorUI::Render(){

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport();

    RenderMenuBar();

    for (auto& panel : panels) {
        panel->Render();
    }

if (ImGuiFileDialog::Instance()->Display("SaveProjectDlg"))
{
    if (ImGuiFileDialog::Instance()->IsOk())
    {
        std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
        Project.SaveToFile(filePath);
    }

    ImGuiFileDialog::Instance()->Close();
}

if (ImGuiFileDialog::Instance()->Display("LoadProjectDlg"))
{
    if (ImGuiFileDialog::Instance()->IsOk())
    {
        std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
        Project.LoadFromFile(filePath);
    }

    ImGuiFileDialog::Instance()->Close();
}

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};

void EditorUI::RenderMenuBar() {

    IGFD::FileDialogConfig cfg;
    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {

            // Save Project
            if (ImGui::MenuItem("Save Project")) {
                ImGuiFileDialog::Instance()->OpenDialog(
                    "SaveProjectDlg",
                    "Save Project",
                    ".json",
                    cfg
                );
            }

            // Load Project
            if (ImGui::MenuItem("Load Project")) {
                ImGuiFileDialog::Instance()->OpenDialog(
                    "LoadProjectDlg",
                    "Load Project",
                    ".json",
                    cfg
                );
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Project Parameter")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    


    }
}
