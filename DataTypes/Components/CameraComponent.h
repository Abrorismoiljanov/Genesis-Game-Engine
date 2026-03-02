#include "Components/components.h"
#include "imgui.h"

class CameraComponent: public Component{    
public:
    float Zoom = 1.0f;

    float near = -1.0f;
    float far = 1.0f;

    json Serialize() const {
        json j;
        j["Zoom"] = Zoom;
        j["near"] = near;
        j["far"] = far;
        return j;
    };
    
    void Deserialize(const json& data) {};
    void OnRemove(AssetManager& AssetManager){};


    virtual std::string Getname() const{
        return "Camera";
    };
    
    void DrawComponentUI(AssetManager& AssetManager){
        ImGui::PushID(ID);
        ImGui::Text("Zoom");
        ImGui::SameLine();
        ImGui::DragFloat("##x", &Zoom, 0.1f, 0.01f, 20.0f);
        ImGui::Text("Near");
        ImGui::SameLine();
        ImGui::DragFloat("##xx", &near, 0.1f, -10.0f, 0.0f);
         ImGui::Text("Far");
        ImGui::SameLine();
        ImGui::DragFloat("###xx", &far, 0.1f, 0.0f, 10.0f);
        ImGui::PopID();
    };
};
