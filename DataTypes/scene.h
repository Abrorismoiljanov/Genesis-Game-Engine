#pragma once
#include "string"
#include "vector"
#include "cstdint"
#include "glm/glm.hpp"
#include "entity.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

struct SceneParam{
    glm::vec4 BackgroundColor = {0.1f, 0.1f, 0.1f, 1.0f};
 
    json Serialize() const {
        json j;
        j["BackgroundColor"] = { BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a };
        return j;
    }

    void Deserialize(const json& j) {
        // Default
        BackgroundColor = {0.1f, 0.1f, 0.1f, 1.0f};

        if (j.contains("BackgroundColor") && j["BackgroundColor"].is_array() && j["BackgroundColor"].size() == 4) {
            BackgroundColor.r = j["BackgroundColor"][0].get<float>();
            BackgroundColor.g = j["BackgroundColor"][1].get<float>();
            BackgroundColor.b = j["BackgroundColor"][2].get<float>();
            BackgroundColor.a = j["BackgroundColor"][3].get<float>();
        }
    }
};

class scene{
 public:
    std::string Scenename;
    uint32_t ID = 0;
    std::vector<uint32_t> EntityIDs;
    SceneParam Param;
    int Camera;

    json Serialize() const {
        json j;
        j["ID"] = ID;
        j["Scenename"] = Scenename;
        j["EntityIDs"] = EntityIDs;
        j["Param"] = Param.Serialize();
        j["Camera"] = Camera;
        return j;
    }

    void Deserialize(const json& j){
        ID = j.value("ID", 0u);
        Scenename = j.value("Scenename", std::string("Scene"));
        EntityIDs = j.value("EntityIDs", std::vector<uint32_t>{});
        Camera = j.value("Camera", -1);
        if (std::find(EntityIDs.begin(), EntityIDs.end(), Camera) == EntityIDs.end())
            Camera = -1;
 
        if (j.contains("Param"))
            Param.Deserialize(j["Param"]);
    } 
    scene(){};
};


