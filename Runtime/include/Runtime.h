#pragma once
#include "DataTypes/project.h"
#include "RuntimeRenderer.h"
#include "ScriptManager.h"
#include "DataTypes/Input.h"

#include "atomic"
#include "thread"
#include "Editor/include/Logger.h"
#include "CollisionSystem.h"

class CoreRuntime{
private:
    SDL_Window* window;
    SDL_GLContext glContext;
    project Project;
    project InitialProject;
    RuntimeRenderer renderer;
    ScriptManager Smanager;
    CollisionSystem CollisionManager;
    Input* RInput = nullptr;
    Logger* Log = nullptr;
    std::atomic<bool> running{false};

    std::thread runtimeThread;
    std::mutex mtx;            

public:
    CoreRuntime();
    void Start(const project& Proj);
    void ResetGame();
    void Stop();
    void Pause();
    void RequestQuit();
    void RunLoop();     
    bool isRunning();
    void SetInput(Input* in);
    void SetLog(Logger* log);
 
    ~CoreRuntime();
};
