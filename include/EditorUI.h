#include "SDL2/SDL.h"
#include "vector"
#include "memory"
#include "Panels.h"
#include "project.h"
#include "SelectedEntity.h"

class EditorUI{
public:
 
    void Init(SDL_Window* window, SDL_GLContext glContext, project& Proj);
    void Update();
    void Render();
    void AddPanel(std::shared_ptr<Panel> panel) {
        panels.push_back(panel);
    }


private:
    project* Project = nullptr;
    std::vector<std::shared_ptr<Panel>> panels; 
    SelectedEntity Selection;

};
