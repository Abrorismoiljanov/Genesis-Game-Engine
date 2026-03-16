#pragma once
#include "DataTypes/project.h"
#include "RuntimeRenderer.h"
#include "ScriptManager.h"

#include "atomic"
#include "thread"

class CoreRuntime{
private:
    SDL_Window* window;
    SDL_GLContext glContext;
    project Project;
    SDL_Event event;
    RuntimeRenderer renderer;
    ScriptManager Smanager;

    std::atomic<bool> running{false};

    std::thread runtimeThread;
    std::mutex mtx;            

public:
    CoreRuntime();
    void Start(const project& Proj);
    void Stop();
    void Pause();
    void RequestQuit();
    void RunLoop();     
    bool isRunning();
    ~CoreRuntime();
};
