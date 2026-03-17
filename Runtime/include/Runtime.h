#pragma once
#include "DataTypes/project.h"
#include "RuntimeRenderer.h"
#include "ScriptManager.h"
#include "DataTypes/Input.h"

#include "atomic"
#include "thread"

class CoreRuntime{
private:
    SDL_Window* window;
    SDL_GLContext glContext;
    Input* RInput = nullptr;
    project Project;
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
    void SetInput(Input* in);
 
    ~CoreRuntime();
};
