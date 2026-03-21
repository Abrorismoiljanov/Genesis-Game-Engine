#include "Runtime/include/ScriptManager.h"

void ScriptManager::RegisterTypes(){

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
 
    lua.new_usertype<CollisionComponent>("Collision",
        "offset", &CollisionComponent::offset,
        "halfSize", &CollisionComponent::halfSize,
        "isTrigger", &CollisionComponent::isTrigger,
        "isStatic", &CollisionComponent::isStatic,
        "layer", &CollisionComponent::layer,
        "mask", &CollisionComponent::mask
    );
}
