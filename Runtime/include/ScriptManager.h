#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "sol/sol.hpp"
#include "project.h"

class ScriptManager{
public:    
    sol::state lua;
    project* Proj;

    std::unordered_map<uint32_t, sol::environment> EntityEnvs;

    void Initialize();   
    void Update(float dt);    
    void InitScripts(uint32_t entityID); 

    void Reset() {
        EntityEnvs.clear();
        lua = sol::state{};
    }
};
