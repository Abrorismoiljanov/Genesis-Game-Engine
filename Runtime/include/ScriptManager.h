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
    Input* input = nullptr; 
    Logger* Log = nullptr;

    void Initialize();   
    void Update(uint32_t entityID, float dt);    
    void InitScripts(uint32_t entityID); 
    void ClearScripts();
 
    void Reset() {
        lua = sol::state{};
    }
};
