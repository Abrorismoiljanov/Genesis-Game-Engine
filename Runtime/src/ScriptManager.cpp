#include "Runtime/include/ScriptManager.h"
#include "DataTypes/Assets/ScriptAsset.h"
#include "sol/sol.hpp"

void ScriptManager::Initialize() {
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package);

    RegisterTypes();
    RegisterGlobals();
    RegisterInput();
}

void ScriptManager::InitScripts(uint32_t entityID) {
    entity* e = Proj->GetEntityByID(entityID);

    for (uint32_t compID : e->ComponentIDs) {
        Component* c = Proj->GetComponentByID(compID);
      
        if (!c || c->Getname() != "Script") continue;
        
        ScriptComponent* sc = static_cast<ScriptComponent*>(c);
        if (sc->Initialized) return;
        sc->Initialized = true;


        std::shared_ptr<ScriptAsset> scriptAsset = Proj->Assets.Get<ScriptAsset>(sc->scriptHandle);
     
        if (!scriptAsset) {
            Log->Error(LogSystem::Script, "Invalid script Handle: " + std::to_string(sc->scriptHandle));
            continue;
        }

        sc->env = sol::environment(lua, sol::create, lua.globals());
 
        sol::load_result chunk = lua.load_file(scriptAsset->Path);

        if (!chunk.valid()) {
            sol::error err = chunk;
            std::cout << err.what() << std::endl;
            continue;
        }
        
        sol::protected_function pf = chunk;

        sol::protected_function_result result = pf(sc->env);

        if (!result.valid()) {
            sol::error err = result;
            std::cout << err.what() << std::endl;
            continue;
        }
        if (result.get_type() != sol::type::table) {
            Log->Error(LogSystem::Script, "Lua script must return a table");
            continue;
        }

        sc->table = result;
        sc->table["self_entity"] = e;  
        sc->onCreate  = sc->table["OnCreate"];
        sc->onUpdate  = sc->table["OnUpdate"];
        sc->onDestroy = sc->table["OnDestroy"];

        if (sc->onCreate.valid()) {
            sol::protected_function pf = sc->onCreate;
            sol::protected_function_result res = pf(e);

            if (!res.valid()) {
                sol::error err = res;
                std::cout << err.what() << std::endl;
            }
 
        }
    }
}

void ScriptManager::Update(uint32_t entityID, float dt) {

    entity* e = Proj->GetEntityByID(entityID);
    

    for (uint32_t compID : e->ComponentIDs) {
        Component* c = Proj->GetComponentByID(compID);
        if (!c || c->Getname() != "Script") continue;

        ScriptComponent* sc = static_cast<ScriptComponent*>(c);

        if (sc->onUpdate.valid()) {
            try {
                sol::protected_function pf = sc->onUpdate;
                sol::protected_function_result res = pf(sc->table, e, dt);

                if (!res.valid()) {
                    sol::error err = res;
                    if (Log)
                        Log->Error(LogSystem::Script, err.what());
                }
            }
            catch (const sol::error& e) {
                if (Log)
                    Log->Error(LogSystem::Script, std::string("Lua runtime exception: ") + e.what());
            }
            catch (const std::exception& e) {
                if (Log)
                    Log->Error(LogSystem::Script, std::string("C++ exception in Lua call: ") + e.what());
            }
            catch (...) {
                if (Log)
                    Log->Error(LogSystem::Script, "Unknown exception in Lua call");
            }
        }
    }
}

void ScriptManager::CallEvent(uint32_t tID, const std::string& funcName, uint32_t oID) {
    auto* target = Proj->GetEntityByID(tID);
    auto* other = Proj->GetEntityByID(oID);

    for (uint32_t compID: target->ComponentIDs) {
        auto* c = Proj->GetComponentByID(compID);
        if (!c) continue;
        if (c->Getname() != "Script") continue; 
            
        auto& scriptComp = static_cast<ScriptComponent&>(*c);
        sol::table& luaTable = scriptComp.table; 
        if (!scriptComp.table.valid()) continue;  
 
        sol::object funcObj = luaTable[funcName];
        if (funcObj.valid() && funcObj.get_type() == sol::type::function) {
            sol::function func = funcObj;
            if (other && target) {
                try {
                    func(scriptComp.table, target, other);
                } catch (const sol::error& err) {
                    if (Log)
                        Log->Error(LogSystem::Script, std::string("Lua error in CallEvent: ") + err.what());
                }
            } else {
                if (Log)
                    Log->Warning(LogSystem::Script, "CallEvent: 'other' entity is null");
            }
        }
    }
}

void ScriptManager::ClearScripts() {
    for (auto& e : Proj->EntityList) {
        entity* ent = Proj->GetEntityByID(e.ID);
        if (!ent) continue;

        for (uint32_t compID : ent->ComponentIDs) {
            Component* c = Proj->GetComponentByID(compID);
            if (!c || c->Getname() != "Script") continue;

            ScriptComponent* sc = static_cast<ScriptComponent*>(c);
            sc->onCreate = sol::nil;
            sc->onUpdate = sol::nil;
            sc->onDestroy = sol::nil;
            sc->table = sol::nil;
            sc->env = sol::nil;
        }
    }
}

