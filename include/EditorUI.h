#include "SDL2/SDL.h"
#include "vector"
#include "memory"
#include "Panels.h"
#include "project.h"
#include "SelectedEntity.h"

class EditorUI{
public:
 
    void Init(SDL_Window* window, SDL_GLContext glContext, project& Proj, Renderer* renderer, bool& running);
    void Update(float deltatime);
    void Render(SDL_Window* window);
    void AddPanel(std::shared_ptr<Panel> panel) {
        panels.push_back(panel);
    }
    void RenderMenuBar(SDL_Window* window);
    EditorUI(project& proj, bool& running);

    bool& Run;
private:
    project& Project;
    std::vector<std::shared_ptr<Panel>> panels; 
    SelectedEntity Selection;
    Renderer* renderer = nullptr;
};
