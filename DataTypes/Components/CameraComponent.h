#include "Components/components.h"
#include "imgui.h"

class CameraComponent: public Component{    
public:
    json Serialize() const {
        json j;

        return j;
    };
    
    void Deserialize(const json& data) {

    };
    void OnRemove(AssetManager& AssetManager){};


    virtual std::string Getname() const{
        return "Camera";
    };
    
    void DrawComponentUI(AssetManager& AssetManager){
        ImGui::Begin("Camera Component");
        ImGui::End();
    };
};
