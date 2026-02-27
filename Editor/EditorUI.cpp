#include "EditorUI.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "SDL2/SDL.h"
#include "ComponentRegisterList.h"
#include "ImGuiFileDialog.h"

EditorUI::EditorUI(project& proj, bool& running): Project(proj), renderer(nullptr), Run(running){}

void EditorUI::Init(SDL_Window* window, SDL_GLContext glContext, project& Proj, Renderer* renderer, bool& running){

    running = Run;
    SelectedScene = 0;

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
//    panels.push_back(std::make_unique<AssetPanel>("Texture Assets", Proj));
    panels.push_back(std::make_unique<Terminal>("Terminal", Proj));
    panels.push_back(std::make_unique<SceneManagerPanel>("SceneManager", Proj, SelectedScene));
    panels.push_back(std::make_unique<SceneParamPanel>("SceneParam", Proj, SelectedScene));
    panels.push_back(std::make_unique<ProjectSettingsPanel>(Proj.Param.name.c_str(), Proj));
    panels.push_back(std::make_unique<EntityList>("Entity List", Proj, Selection, SelectedScene));
    panels.push_back(std::make_unique<Inspector>("Inspector", Proj, Selection));
    panels.push_back(std::make_unique<Viewport>("Viewport", Proj, Selection, renderer, SelectedScene));

};

void EditorUI::Update(float deltaTime){
    for (auto& panel : panels) {
        panel->Update(deltaTime);
    }
};

void EditorUI::Render(SDL_Window* window){

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport();

    RenderMenuBar(window);

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

void EditorUI::RenderMenuBar(SDL_Window* window) {

    IGFD::FileDialogConfig cfg;
    cfg.path = "/home/abror/Project/GGE/assets/";
    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {

            if (ImGui::MenuItem("Save Project")) {
                ImGuiFileDialog::Instance()->OpenDialog(
                    "SaveProjectDlg",
                    "Save Project",
                    ".json",
                    cfg
                );
            }

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

        if(ImGui::BeginMenu("Editor")){
                Uint32 flags = SDL_GetWindowFlags(window);
                bool isFullscreen = flags & SDL_WINDOW_FULLSCREEN;

            if (ImGui::MenuItem("Fullscreen", nullptr, isFullscreen)) {
 
                if (isFullscreen) {
                    SDL_SetWindowFullscreen(window, 0);
                    SDL_SetWindowSize(window, 1920, 1080); 
                }
                else {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
            }
            if (ImGui::MenuItem("Quit")){
                Run = false;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();

    }
}
