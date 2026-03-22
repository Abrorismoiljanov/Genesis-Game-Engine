#define IMGUI_DEFINE_MATH_OPERATORS
#include "project.h"
#include "EditorUI.h"
#include "Renderer.h"
#include "Logger.h"
#include "Runtime/include/Runtime.h"
#include "DataTypes/Input.h"
#include "CommandSystem.h"

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
    Input InputManager;
    Logger Log;
    CommandSystem CmdSystem;

    Uint64 lastTime = 0;   
    float deltaTime = 0.0f; 

    void InitCommands();

    void PollEvent(bool& running);
    void Update();
    void Render();

public:
 

    app();  
    bool Init();
    void Run();

    ~app();
};

