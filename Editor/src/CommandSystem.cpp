#include "Editor/include/CommandSystem.h"


void CommandSystem::Execute(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> args;
    std::string word;

    while (iss >> word)
        args.push_back(word);

    if (args.empty())
        return;

    std::string cmdName = args[0];
    args.erase(args.begin());

    auto it = commands.find(cmdName);
    if (it != commands.end()) {
        log->Info(LogSystem::Engine, "> " + std::string(cmdName));
        it->second.Execute(args);
    } else {
        std::string msg = "Unknown command:" + cmdName;
        log->Info(LogSystem::Engine, msg);
    }
}
