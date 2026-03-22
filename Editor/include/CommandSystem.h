#pragma once
#include "iostream"
#include "functional"
#include <sstream>   
#include "Logger.h"

struct Command {
    std::function<void(const std::vector<std::string>& args)> Execute;
    std::string Description;

    Command() = default;
 
    Command(std::function<void(const std::vector<std::string>&)> func, const std::string& desc = "")
        : Execute(func), Description(desc) {}
};

class CommandSystem {
public:

 
    void Register(
        const std::string& name,
        std::function<void(const std::vector<std::string>& args)> func,
        const std::string& description = ""){
 
        commands[name] = { func, description };

    }


    const std::unordered_map<std::string, Command>& GetAll() const {
        return commands;
    }
    void Execute(const std::string& input);

    Logger* log = nullptr;

private:
    std::unordered_map<std::string, Command> commands;
};
