#pragma once
#include "string"
#include "vector"
#include "cstdint"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

struct TransformData{
    glm::vec3 position {0.0f};
    float rotation {0.0f}; 
    glm::vec3 scale    {1.0f};
};

class entity{
public:
    std::string name;
    uint32_t ID = 0;
    std::vector<uint32_t> ComponentIDs; 

    TransformData transform;


    json Serialize() const {
        json j;
        j["position"] = { transform.position.x, transform.position.y, transform.position.z };
        j["rotation"] = transform.rotation;
        j["scale"]    = { transform.scale.x,    transform.scale.y,    transform.scale.z };
        return j;
    }

    void Deserialize(const json& data) {

        transform.position = {0.0f, 0.0f, 0.0f};
        transform.rotation = 0.0f;
        transform.scale    = {1.0f, 1.0f, 1.0f};


        if (data.contains("position") && data["position"].is_array() && data["position"].size() == 3) {
            transform.position.x = data["position"][0].get<float>();
            transform.position.y = data["position"][1].get<float>();
            transform.position.z = data["position"][2].get<float>();
        }

        if (data.contains("rotation")) {
            transform.rotation = data["rotation"].get<float>();
        }

        if (data.contains("scale") && data["scale"].is_array() && data["scale"].size() == 3) {
            transform.scale.x = data["scale"][0].get<float>();
            transform.scale.y = data["scale"][1].get<float>();
            transform.scale.z = data["scale"][2].get<float>();
        }
    }

    glm::mat4 GetTransformMatrix() const{

        glm::mat4 mat = glm::mat4(1.0f);

        mat = glm::translate(mat, transform.position);

        mat = glm::rotate(
            mat,
            glm::radians(transform.rotation),
            glm::vec3(0.0f, 0.0f, 1.0f)
        );
        mat = glm::scale(mat, transform.scale);
        return mat;
    }


    void DrawInfoUI();

private:
};

