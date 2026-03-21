#include "Runtime/include/ScriptManager.h"

void ScriptManager::RegisterGlobals(){
 
    lua["Log"] = [this](const std::string& msg){ 
        if (Log) {
            Log->Info(LogSystem::Script, msg); 
        }
    };
   
    lua.set_function("GetComponent", [this](entity& e, const std::string& name) -> sol::object {
        for (uint32_t compID : e.ComponentIDs) {
            Component* c = Proj->GetComponentByID(compID);
            if (c && c->Getname() == name)
                return c->PushToLua(lua);
        }
        return sol::nil;
    });

    
    for (int sc = SDL_SCANCODE_UNKNOWN; sc < SDL_NUM_SCANCODES; ++sc) {
        const char* name = SDL_GetScancodeName((SDL_Scancode)sc);
 
        if (name && name[0] != '\0') {
            std::string keyName = "KEY_" + std::string(name);

            std::transform(keyName.begin(), keyName.end(), keyName.begin(), ::toupper);
            std::replace(keyName.begin(), keyName.end(), ' ', '_');

            lua[keyName] = sc;
        }
    }
}
