#pragma once

#include "iostream"
#include "string"
#include "vector"
#include "SDL2/SDL.h"
#include "memory"
#include "algorithm"

#include "scene.h"
#include "entity.h"
#include "components.h"
#include "AssetManager.h"

struct ProjectParam{
    std::string name = "Default Project";
    int WindowHeight = 1920;
    int WindowWidth = 1080;
    SDL_WindowFlags WindowParam;
};

struct project{

    ProjectParam Param;

    bool valid = false;
    std::vector<scene> SceneList;
    std::vector<entity> EntityList;
    std::vector<std::unique_ptr<Component>> ComponentList;
    AssetManager Assets;
    uint32_t activeSceneID; 
    uint32_t NextComponentID = 0;
    uint32_t NextEntityID = 0;

    entity* GetEntityByID(uint32_t id) {
        for (auto& e : EntityList)
            if (e.ID == id) return &e;
        return nullptr;
    }

    void AddEntity(uint32_t SceneID){
        auto e = entity();
        e.name = "Entity";
        for (auto& scene: SceneList) {
            if (scene.ID == SceneID) {
                scene.EntityIDs.push_back(e.ID);
                EntityList.push_back(e);
            }
        }
    };
    void DeleteEntity(uint32_t EntityID){
        ComponentList.erase(
            std::remove_if(
                ComponentList.begin(),
                ComponentList.end(),
                [EntityID](const std::unique_ptr<Component>& c){
                    return c->OwnerEntityID == EntityID;
                }
            ),
            ComponentList.end()
        );
    
        EntityList.erase(
            std::remove_if(
                EntityList.begin(),
                EntityList.end(),
                [EntityID](const entity& e) {
                return e.ID == EntityID;
                }
            ),
            EntityList.end()
        );
        for (auto& s: SceneList) {
            auto& ids = s.EntityIDs;
            ids.erase(
                std::remove(ids.begin(), ids.end(), EntityID),
                ids.end()
            );
        }

    };

    template<typename T, typename... Args>
    T* AddComponent(uint32_t entityID, Args&&... args){
        static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->ID = NextComponentID++;  
        comp->OwnerEntityID = entityID;

        T* raw = comp.get();
        ComponentList.push_back(std::move(comp));
        entity* e = GetEntityByID(entityID);
        if (!e) return nullptr;
        if (e) {
            e->ComponentIDs.push_back(raw->ID);
        }
        return raw;
    }


    Component* GetComponentByID(uint32_t id) {
        for (auto& c : ComponentList)
            if (c->ID == id) return c.get();
        return nullptr;
    }
};

struct ComponentDescriptor {
    std::string name;
    bool allowDupe;
    void (*add)(project&, uint32_t entityID);
    bool (*has)(project&, uint32_t entityID);
};

template<typename T>
    bool HasComponent(project& proj, uint32_t entityID) {
    entity* e = proj.GetEntityByID(entityID);
    if (!e) return false;

    for (uint32_t cid : e->ComponentIDs) {
        Component* c = proj.GetComponentByID(cid);
        if (dynamic_cast<T*>(c)) return true;
    }
    return false;
}

