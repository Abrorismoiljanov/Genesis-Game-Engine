#include "Runtime/include/ScriptManager.h"

void ScriptManager::RegisterInput(){
 
    Input*& runtimeInput = input;
    
    lua["Input"] = lua.create_table();

    lua["Input"]["IsKeyDown"] = [runtimeInput](int key) -> bool {
        return runtimeInput && runtimeInput->IsKeyDown(key);
    };
    lua["Input"]["IsKeyPressed"] = [runtimeInput](int key) -> bool {
        return runtimeInput && runtimeInput->IsKeyPressed(key);
    };
    lua["Input"]["IsKeyReleased"] = [runtimeInput](int key) -> bool {
        return runtimeInput && runtimeInput->IsKeyReleased(key);
    };

}
