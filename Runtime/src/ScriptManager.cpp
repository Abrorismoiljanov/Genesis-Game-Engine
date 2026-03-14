#include "Runtime/include/ScriptManager.h"
#include "DataTypes/Assets/ScriptAsset.h"
#include "sol/sol.hpp"
void ScriptManager::Initialize() {
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package);

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
 
 
    lua["Log"] = [](const std::string& msg){ std::cout << "[Lua] " << msg << "\n"; };
}

void ScriptManager::RunScript(uint32_t entityID) {
        
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

        auto& env = EntityEnvs[entityID];
        if (!env.valid()) {
            env = sol::environment(lua, sol::create, lua.globals());
        }
         
        env["self"] = e;
        lua.script_file(scriptAsset->Path, env);
    }
}
