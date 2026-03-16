#include "Runtime/include/Runtime.h"

CoreRuntime::CoreRuntime(){}

void CoreRuntime::Start(const project& Proj){
    Project = Proj.Clone();

    Smanager.Reset();
    Smanager.Proj = &Project;
    Smanager.Initialize();

    runtimeThread = std::thread(&CoreRuntime::RunLoop, this);
}

void CoreRuntime::RunLoop(){
    Project.valid = true;

    running = true;
 
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL init failed" << '\n';
    }

    if (Project.valid) {
        window = SDL_CreateWindow(
            Project.Param.name.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            Project.Param.WindowWidth,
            Project.Param.WindowHeight,
            Project.Param.WindowParam);
    }else {
        window = SDL_CreateWindow("No Project Attached", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    }
    if (!window){
        std::cout << "window creation failed" << '\n';
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cout << "GL context creation failed" << '\n';
    }
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
         std::cout << "GLEW init failed\n";
    }
    renderer.Init(Project.Param.WindowWidth, Project.Param.WindowHeight, Project, window);

    for (auto& eID : Project.EntityList) {
        Smanager.InitScripts(eID.ID);
    }

    float dt = 0.0016f;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }

        renderer.BeginFrame(Project, Project.activeSceneID);

 
        for (auto& eID: Project.EntityList) {
            Smanager.Update(eID.ID, dt);
        }

        renderer.Render(Project, Project.activeSceneID);
        renderer.EndFrame(window);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    Smanager.ClearScripts();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
};
void CoreRuntime::Stop(){
    running = false;
    if(runtimeThread.joinable())
        runtimeThread.join(); 
};

bool CoreRuntime::isRunning(){
    return running;
};

CoreRuntime::~CoreRuntime(){
    Stop();
};
