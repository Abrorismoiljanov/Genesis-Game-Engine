#include "Editor/include/App.h"
#include "string"

void app::InitCommands() {

    CmdSystem.Register("help", [&](const std::vector<std::string>& args){
        for (auto& [name, cmd] : CmdSystem.GetAll()) {
            Log.Info(LogSystem::Engine, name + " - " + cmd.Description);
        }
    }, "Show all commands");

    CmdSystem.Register("clear", [&](const std::vector<std::string>& args){
        Log.Clear();
    }, "Clear terminal logs");

    CmdSystem.Register("run", [&](const std::vector<std::string>& args){
        if (runtime.isRunning()) {
            Log.Warning(LogSystem::Engine, "Game is already running!");
        }else {
            Log.Clear();
            runtime.Start(Project);
        }
    }, "Start the Game");

    CmdSystem.Register("stop", [&](const std::vector<std::string>& args){
        runtime.Stop();
        Log.Info(LogSystem::Engine, "Runtime stopped");
    }, "Stop the runtime");
}
