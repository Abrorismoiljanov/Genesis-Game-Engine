#include "CompRegister.h"
#include "transformcomponent.h"
#include "MeshComponent.h"

void RegisterAllComponents() {
    auto& reg = ComponentRegistry::Get();
        
    reg.Register<TransformComponent>("Transform", false);
    reg.Register<MeshComponent>("Mesh", true);
}
