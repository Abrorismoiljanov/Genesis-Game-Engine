#include "SDL2/SDL.h"
#include "project.h"

class CoreRuntime{
private:
    SDL_Window* window;
    SDL_GLContext glContext;
    project Project;

public:
    CoreRuntime();
    void Init();
    void Run();
    ~CoreRuntime();
};
