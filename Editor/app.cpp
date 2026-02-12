#include "iostream"
#include "App.h"
#include "GL/glew.h"
#include "SDL2/SDL.h"

#include "imgui.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "imgui_internal.h"

#include "transformcomponent.h"

app::app():
window(nullptr),
glContext(nullptr)
{}

bool app::Init(){
    
    running = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL init failed" << '\n';
        return false;
    }

    std::string title = Project.Param.name + " Editor";
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              1920,
                              1080,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window){
        std::cout << "window creation failed" << '\n';
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cout << "GL context creation failed" << '\n';
        return false;
    }
    
    if (glewInit() != GLEW_OK) {
        return false;
    }
    



    UI.Init(window, glContext, Project, &renderer);
    renderer.Init(1280, 720);

    return true;

};


void app::Run(){
    while (running) {
        PollEvent(running);
        Update();
        Render();
    }
}


void app::PollEvent(bool& running){
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
            running = false;
            break;

            case SDL_KEYDOWN:
            if (!ImGui::GetIO().WantCaptureKeyboard) {
            
                }
            break;
            
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
            if (!ImGui::GetIO().WantCaptureMouse) {
            
            }
            break;
        }

    }
};

void app::Update(){
}

void app::Render(){
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    
    renderer.BeginFrame(w, h);
    if (!Project.SceneList.empty())
        renderer.Render(Project.SceneList[0], Project);
 
    renderer.EndFrame();

    UI.Render();
    SDL_GL_SwapWindow(window);
}

app::~app(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    if (glContext) SDL_GL_DeleteContext(glContext);
    if (window) SDL_DestroyWindow(window);

    SDL_Quit();
}
