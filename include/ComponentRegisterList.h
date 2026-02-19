#include "CompRegister.h"
#include "transformcomponent.h"
#include "SpriteComponent.h"

void RegisterAllComponents() {
    auto& reg = ComponentRegistry::Get();
        
    reg.Register<TransformComponent>("Transform", false);
    reg.Register<SpriteComponent>("Sprite", true);
}
