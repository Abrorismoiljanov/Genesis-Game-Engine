#include "Runtime/include/Runtime.h"

CoreRuntime::CoreRuntime(){}

void CoreRuntime::Init(std::string projectFile){
    
    running = true;

    if (!projectFile.empty())
    {
        if (!Project.LoadFromFile(projectFile))
        {
            std::cerr << "[Runtime] Failed to load project: " << projectFile << std::endl;
            Project.valid = false;
        }
        else
        {
            Project.valid = true;
        }
    }
    else
    {
        Project.valid = false;
    }
 
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
}

void CoreRuntime::Run(){
    while (running) {
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }
        renderer.BeginFrame(Project, Project.activeSceneID);
        renderer.Render(Project, Project.activeSceneID);
        renderer.EndFrame(window);
    }
}

CoreRuntime::~CoreRuntime(){};
