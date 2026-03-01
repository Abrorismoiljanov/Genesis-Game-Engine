#include "CompRegister.h"
#include "DataTypes/Components/SpriteComponent.h"
#include "DataTypes/Components/CameraComponent.h"

void RegisterAllComponents() {
    auto& reg = ComponentRegistry::Get();
        
    reg.Register<SpriteComponent>("Sprite", true);
    reg.Register<CameraComponent>("Camera", false);
}
