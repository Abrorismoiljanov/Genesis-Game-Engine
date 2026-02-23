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
#include "SpriteComponent.h"
#include "AssetManager.h"
#include "nlohmann/json.hpp"
#include "transformcomponent.h"
#include "Assets/MaterialAsset.h"
#include "unordered_set"
#include "fstream"

using json = nlohmann::json;

struct ProjectParam{
    std::string name = "Default Project";
    int WindowHeight = 1920;
    int WindowWidth = 1080;
    SDL_WindowFlags WindowParam;
};

struct project{

    ProjectParam Param = ProjectParam();

    bool valid = false;
    std::vector<scene> SceneList;
    std::vector<entity> EntityList;
    std::vector<std::unique_ptr<Component>> ComponentList;
    AssetManager Assets;
    uint32_t activeSceneID = 0; 
    uint32_t NextComponentID = 0;
    uint32_t NextEntityID = 0;
    uint32_t NextSceneID = 0;

  json Serialize() const {
        json j;
        json& pj = j["project"];

        pj["name"] = Param.name;
        pj["window"]["width"] = Param.WindowWidth;
        pj["window"]["height"] = Param.WindowHeight;
        pj["window"]["flags"] = static_cast<uint32_t>(Param.WindowParam);
        pj["activeSceneID"] = activeSceneID;
        pj["nextEntityID"] = NextEntityID;
        pj["nextComponentID"] = NextComponentID;


        pj["entities"] = json::array();
    for (const auto& e : EntityList) {
        json ent;
        ent["id"] = e.ID;
        ent["name"] = e.name;
        
        pj["entities"].push_back(ent);
    }

pj["scenes"] = json::array();
for (const auto& sc : SceneList) {
    json s;
    s["id"]        = sc.ID;
    s["Scenename"] = sc.Scenename;
    s["EntityIDs"] = sc.EntityIDs;
    pj["scenes"].push_back(s);
}
pj["nextSceneID"] = NextSceneID;

    // Components (you already have this part)
    pj["components"] = json::array();
    for (const auto& ptr : ComponentList) {
        const auto& c = *ptr;
        json comp;
        comp["id"] = c.ID;
        comp["owner"] = c.OwnerEntityID;
        comp["type"] = c.Getname();
        comp["data"] = c.Serialize();
        pj["components"].push_back(comp);
    }

pj["asset_manifest"] = json::array();

// Collect unique material handles used by sprites
std::unordered_set<AssetHandle> used_handles;
for (const auto& ptr : ComponentList) {
    if (ptr->Getname() == "Sprite") {
        auto* sprite = static_cast<const SpriteComponent*>(ptr.get());
        if (sprite->materialHandle != INVALID_ASSET) {
            used_handles.insert(sprite->materialHandle);
        }
    }
}

// Save path for each used material
for (AssetHandle h : used_handles) {
    auto mat = Assets.Get<MaterialAsset>(h);
    if (mat && mat->GetTexture()) {
        json entry;
        entry["handle"]      = h;
        entry["type"]        = "Material";
        entry["texture_path"] = mat->GetTexture()->Path;  // the key field!
        // optional: entry["material_name"] = mat->Name; etc.
        pj["asset_manifest"].push_back(entry);

            }
        }
        return j;
    }

    void Deserialize(const json& j) {
        const json& pj = j.at("project");

        Param.name = pj.at("name").get<std::string>();
        Param.WindowWidth = pj.at("window").at("width").get<int>();
        Param.WindowHeight = pj.at("window").at("height").get<int>();
        Param.WindowParam = static_cast<SDL_WindowFlags>(pj.at("window").at("flags").get<uint32_t>());

        activeSceneID = pj.at("activeSceneID").get<uint32_t>();
        NextEntityID = pj.at("nextEntityID").get<uint32_t>();
        NextComponentID = pj.at("nextComponentID").get<uint32_t>();

        SceneList.clear();
        EntityList.clear();
        ComponentList.clear();

        if (pj.contains("entities")) {
            for (const auto& ej : pj["entities"]) {
                entity e;
                e.ID   = ej.value("id", 0u);
                e.name = ej.value("name", "Entity");
                EntityList.push_back(e);
            }
        }
        std::cout << "[DEBUG] Loaded " << EntityList.size() << " entities\n";
 
        if (pj.contains("scenes")) {
            for (const auto& sj : pj["scenes"]) {
                scene sc;
                sc.ID        = sj.value("id", 0u);
                sc.Scenename = sj.value("Scenename", "New Scene");
                sc.EntityIDs = sj.value("EntityIDs", std::vector<uint32_t>{});
                SceneList.push_back(sc);
            }
        }
        std::cout << "[DEBUG] Loaded " << SceneList.size() << " scenes\n";     


        if (pj.contains("components")) {
        for (const auto& cj : pj["components"]) {
            std::string type   = cj.value("type", "");
            uint32_t id        = cj.value("id",   0u);
            uint32_t owner     = cj.value("owner", 0u);
            json data          = cj["data"];

            std::unique_ptr<Component> comp = nullptr;

            if (type == "Transform") {
                comp = std::make_unique<TransformComponent>();
            }
            else if (type == "Sprite") {
                comp = std::make_unique<SpriteComponent>();
            }
            // add more types here later

            if (!comp) {
                // unknown type → skip or log
                continue;
            }

            comp->ID            = id;
            comp->OwnerEntityID = owner;
            comp->Deserialize(data);   // calls the derived version you implemented

            ComponentList.push_back(std::move(comp));
        }
    }

    // 6. Rebuild links: entity.ComponentIDs ← from all loaded components
    for (auto& e : EntityList) {
        e.ComponentIDs.clear();
    }

    for (const auto& comp_ptr : ComponentList) {
        if (entity* owner = GetEntityByID(comp_ptr->OwnerEntityID)) {
            owner->ComponentIDs.push_back(comp_ptr->ID);
        }
    }

    // 7. Optional: safety – make sure Next* counters are at least max+1
    for (const auto& e : EntityList) {
        NextEntityID = std::max(NextEntityID, e.ID + 1);
    }
    for (const auto& c : ComponentList) {
        NextComponentID = std::max(NextComponentID, c->ID + 1);
    }
    for (const auto& s : SceneList) {
        NextSceneID = std::max(NextSceneID, s.ID + 1);
    }

if (pj.contains("asset_manifest")) {
    std::cout << "[DEBUG] Found asset_manifest with " << pj["asset_manifest"].size() << " entries\n";

    for (const auto& entry : pj["asset_manifest"]) {
        std::string type = entry.value("type", "");
        AssetHandle saved_handle = entry.value("handle", INVALID_ASSET);
        std::string texture_path = entry.value("texture_path", "");

        if (type != "Material" || texture_path.empty() || saved_handle == INVALID_ASSET) {
            std::cout << "[DEBUG] Skipping invalid asset entry\n";
            continue;
        }

        // Create fresh texture
        auto new_tex = std::make_shared<TextureAsset>();
        new_tex->LoadFromFile(texture_path);


        new_tex->UploadToGPU();  // or whatever method you use to prepare for rendering

        // Create material and attach texture
        auto new_mat = std::make_shared<MaterialAsset>();
        new_mat->SetTexture(new_tex);

        // Register it back — ideally with the same handle
        AssetHandle new_handle = Assets.RegisterAsset(new_mat);  // ← your normal registration

        // If your AssetManager allows forcing the handle, do:
        // AssetHandle new_handle = Assets.RegisterAssetWithHandle(new_mat, saved_handle);
        // If not, you may need to remap handles (see below)

        std::cout << "[DEBUG] Reloaded material from " << texture_path 
                  << " with handle " << new_handle << "\n";
    }
} else {
    std::cout << "[DEBUG] No asset_manifest found — no materials reloaded\n";
}

    }


    bool SaveToFile(const std::string& path) const {
        std::ofstream file(path);
        if (!file.is_open()) return false;

        json j = Serialize();
        file << j.dump(4);
        return true;
    }

    bool LoadFromFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) return false;

        json j;
        file >> j;
        Deserialize(j);
        return true;
    }

    entity* GetEntityByID(uint32_t id) {
        for (auto& e : EntityList)
            if (e.ID == id) return &e;
        return nullptr;
    }

    void AddEntity(uint32_t SceneID){
        auto e = entity();
        e.name = "Entity";
        e.ID = NextEntityID++;
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

