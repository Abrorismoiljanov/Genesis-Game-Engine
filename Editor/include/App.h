#define IMGUI_DEFINE_MATH_OPERATORS
#include "project.h"
#include "EditorUI.h"
#include "Renderer.h"
#include "Runtime/include/Runtime.h"

class app{
private:

    SDL_Window* window;
    SDL_GLContext glContext;

    SDL_Event event;
    bool running;

    project Project;
    EditorUI UI;
    Renderer renderer;
    CoreRuntime runtime;

    Uint64 lastTime = 0;   
    float deltaTime = 0.0f; 

    void PollEvent(bool& running);
    void Update();
    void Render();

public:
 

    app();  
    bool Init();
    void Run();

    ~app();
};

