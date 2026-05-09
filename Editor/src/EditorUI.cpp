#include "Editor/include/EditorUI.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "SDL2/SDL.h"
#include "Editor/include/ComponentRegisterList.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "Editor/include/IconsFontAwesome6.h"
#include "Editor/include/Themes.h"

EditorUI::EditorUI(project& proj, bool& running): Project(proj), renderer(nullptr), Run(running){}

void EditorUI::Init(SDL_Window* window,
                    SDL_GLContext glContext,
                    project& Proj,
                    Renderer* renderer, 
                    bool& running,
                    CoreRuntime* runtime,
                    Logger* Log, 
                    CommandSystem* cmdSystem){

    Runtime = runtime;
    CmdSystem = cmdSystem;
    running = Run;
    SelectedScene = 0;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    float fontSize = 16.0f;

    io.Fonts->AddFontFromFileTTF(
        "assets/fonts/JetBrainsMono-2.304/fonts/ttf/JetBrainsMono-Medium.ttf",
        fontSize
    );

    ImFontConfig config;
    config.MergeMode = true;
    config.PixelSnapH = true;

    static const ImWchar icon_ranges[] ={
        ICON_MIN_FA,
        ICON_MAX_FA,
        0
    };

    io.Fonts->AddFontFromFileTTF(
        "assets/fonts/fontawesome-free-7.2.0-desktop/otfs/Font Awesome 7 Free-Solid-900.otf",
        fontSize,
        &config,
        icon_ranges
    );
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Optional style tweaks
    ImGui::StyleColorsDark();
    ImGui::GetStyle().WindowRounding = 6.0f;
    ImGui::GetStyle().FrameRounding = 4.0f;


    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");

    RegisterAllComponents();
    panels.push_back(std::make_unique<Terminal>("Terminal", Proj, Log, CmdSystem));
    panels.push_back(std::make_unique<SceneManagerPanel>("SceneManager", Proj, SelectedScene));
    panels.push_back(std::make_unique<SceneParamPanel>("SceneParam", Proj, SelectedScene));
    panels.push_back(std::make_unique<ProjectSettingsPanel>(Proj.Param.name.c_str(), Proj));
    panels.push_back(std::make_unique<EntityList>("Entity List", Proj, Selection, SelectedScene));
    panels.push_back(std::make_unique<Inspector>("Inspector", Proj, Selection, renderer));
    panels.push_back(std::make_unique<Viewport>("Viewport", Proj, Selection, renderer, SelectedScene, *runtime));

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
    cfg.path = "assets/";
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

            if (ImGui::BeginMenu("Themes")) {  // <-- this is now a submenu, not MenuItem
                struct ThemeOption {
                    const char* name;
                    void (*apply)();
                };

                // List of themes
                static ThemeOption themes[] = {
                    { "Dark", [](){ ImGui::StyleColorsDark(); } },
                    { "Light", [](){ ImGui::StyleColorsLight(); } },
                    { "Classic", [](){ ImGui::StyleColorsClassic(); } },
                    { "Nord", [](){ ApplyNordTheme(); } },         
                    { "Catppuccin Mocha", [](){ ApplyCatppuccinMocha(); } },
                    { "Gruvbox Dark", [](){ ApplyGruvboxDark(); } },
                    { "Ayu Dark", [](){ ApplyAyuDark(); } },
                };

                static int currentTheme = 0; // track selected theme

                for (int i = 0; i < IM_ARRAYSIZE(themes); i++) {
                    bool selected = (currentTheme == i);
            
                    // Display checkmark icon for current theme
                    if (ImGui::MenuItem(themes[i].name, nullptr, selected)) {
                        currentTheme = i;
                        themes[i].apply(); // apply selected theme
                    }
                }

                    ImGui::EndMenu();
            }
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


