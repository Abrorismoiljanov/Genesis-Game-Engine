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

    auto frameStart = std::chrono::high_resolution_clock::now();
    auto last = std::chrono::high_resolution_clock::now();
 
    while (running) {
  
        auto now = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float>(now - last).count();
        last = now;   

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    RequestQuit();
                }
            }
        }

        renderer.BeginFrame(Project, Project.activeSceneID);

 
        for (auto& eID: Project.EntityList) {
            Smanager.Update(eID.ID, dt);
        }

        renderer.Render(Project, Project.activeSceneID);
        renderer.EndFrame(window);

        const float targetFrameTime = 1.0f / 60.0f;


        auto frameEnd = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float>(frameEnd - frameStart).count();

        if (frameTime < targetFrameTime) {
            std::this_thread::sleep_for(
                std::chrono::duration<float>(targetFrameTime - frameTime)
            );
        }
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
    return running.load();
};

void CoreRuntime::RequestQuit(){
    running = false;
};

CoreRuntime::~CoreRuntime(){
    Stop();
};
