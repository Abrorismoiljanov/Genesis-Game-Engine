#include "Runtime/include/ScriptManager.h"

void ScriptManager::RegisterGlobals(){
 
    lua["Log"] = [this](const std::string& msg){ 
        if (Log) {
            Log->Info(LogSystem::Script, msg); 
        }
    };

    
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
