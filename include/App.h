#include "project.h"
#include "EditorUI.h"
#include "Renderer.h"

class app {
private:

    SDL_Window* window;
    SDL_GLContext glContext;

    SDL_Event event;
    bool running;

    project Project;
    EditorUI UI;
    Renderer renderer;

    void PollEvent(bool& running);
    void Update();
    void Render();

public:
    app();  
    bool Init();
    void Run();

    ~app();
};

