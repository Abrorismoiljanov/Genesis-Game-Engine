#include "project.h"

class ComponentRegistry{
public:
    static ComponentRegistry& Get(){
        static ComponentRegistry instance;
        return instance;
    };

    template<typename T>
    void Register(const std::string& name, bool allowDupe) {
        static_assert(std::is_base_of<Component, T>::value);

        ComponentDescriptor desc;
        desc.name = name;
        desc.allowDupe = allowDupe;
        desc.add = [](project& proj, uint32_t entityID) {
            proj.AddComponent<T>(entityID);
        };

        desc.has = [](project& proj, uint32_t entityID) {
        return HasComponent<T>(proj, entityID);
        };

        components.push_back(std::move(desc));
    }
    const std::vector<ComponentDescriptor>& All() const {
        return components;
    }

private:
        std::vector<ComponentDescriptor> components;
};
