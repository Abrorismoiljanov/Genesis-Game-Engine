#include "project.h"
#include "RuntimeRenderer.h"

class CoreRuntime{
private:
    SDL_Window* window;
    SDL_GLContext glContext;
    bool running;
    project Project;
    SDL_Event event;
    RuntimeRenderer renderer;

public:
    CoreRuntime();
    void Init(std::string projectFile);
    void Run();
    ~CoreRuntime();
};
