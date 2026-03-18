#include "Runtime/include/ScriptManager.h"
#include "DataTypes/Assets/ScriptAsset.h"
#include "sol/sol.hpp"

void ScriptManager::Initialize() {
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package);

    Input*& runtimeInput = input;

    lua.new_usertype<glm::vec3>("Vec3",
                                "x", &glm::vec3::x,
                                "y", &glm::vec3::y,
                                "z", &glm::vec3::z
                                );

    lua.new_usertype<TransformData>("TransformData",
                                    "position", sol::property([](TransformData& t) -> glm::vec3& { return t.position; }),
                                    "rotation", &TransformData::rotation,
                                    "scale", sol::property([](TransformData& t) -> glm::vec3& { return t.scale; })
                                    );


    lua.new_usertype<entity>("Entity",
                             "name", &entity::name,
                             "ID", &entity::ID,
                             "transform", &entity::transform
                             );
 
 
    lua["Log"] = [this](const std::string& msg){ 
        if (Log) {
            Log->Info(LogSystem::Script, msg); 
        }
    };

    lua["Input"] = lua.create_table();
    
    lua["KEY_SPACE"] = SDL_SCANCODE_SPACE;
    lua["KEY_A"] = SDL_SCANCODE_A;
    lua["KEY_D"] = SDL_SCANCODE_D;
    lua["KEY_W"] = SDL_SCANCODE_W;
    lua["KEY_S"] = SDL_SCANCODE_S;


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

void ScriptManager::InitScripts(uint32_t entityID) {
        
    entity* e = Proj->GetEntityByID(entityID);
        
    for (uint32_t compID : e->ComponentIDs) {
        Component* c = Proj->GetComponentByID(compID);
      
        if (!c || c->Getname() != "Script") continue;

        
        ScriptComponent* sc = static_cast<ScriptComponent*>(c);
 
        std::shared_ptr<ScriptAsset> scriptAsset = Proj->Assets.Get<ScriptAsset>(sc->scriptHandle);
     
        if (!scriptAsset) {
            std::cerr << "[ScriptManager] Invalid script handle: " << sc->scriptHandle << std::endl;
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
            std::cout << "[ScriptManager] Lua script must return a table\n";
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

