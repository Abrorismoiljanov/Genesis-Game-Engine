#include "CompRegister.h"
#include "DataTypes/Components/SpriteComponent.h"
#include "DataTypes/Components/ScriptComponent.h"
#include "Components/CollisionComponent.h"
void RegisterAllComponents() {
    auto& reg = ComponentRegistry::Get();
        
    reg.Register<SpriteComponent>("Sprite", true);
    reg.Register<ScriptComponent>("Script", true);
    reg.Register<CameraComponent>("Camera", false);
    reg.Register<CollisionComponent>("Collision", true);
}
