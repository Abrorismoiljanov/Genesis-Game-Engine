#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "sol/sol.hpp"
#include "project.h"
#include "DataTypes/Input.h"
#include "Editor/include/Logger.h"

class ScriptManager{
public:    
    sol::state lua;
    project* Proj;
    bool Restart = false;
    Input* input = nullptr; 
    Logger* Log = nullptr;

    void Initialize();   
    void Update(uint32_t entityID, float dt);    
    void InitScripts(uint32_t entityID); 
    void ClearScripts();

    void CallEvent(uint32_t tID, const std::string& funcName, uint32_t oID);
    bool HasMethod(entity& e, const std::string& name);
    void CallMethod(entity& target, const std::string& method, entity& caller);

    void RegisterTypes();
    void RegisterGlobals();
    void RegisterInput();

    void Reset() {
        lua = sol::state{};
    }
};
