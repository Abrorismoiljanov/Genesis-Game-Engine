#include "CompRegister.h"
#include "transformcomponent.h"
#include "SpriteComponent.h"

void RegisterAllComponents() {
    auto& reg = ComponentRegistry::Get();
        
    reg.Register<SpriteComponent>("Sprite", true);
}
