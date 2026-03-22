#include "Editor/include/Logger.h"
#include "ScriptManager.h"
#include "DataTypes/project.h"

class CollisionSystem {
public:
    void Init(Logger* logger, project* Project, ScriptManager* scriptmanager){
        log = logger;
        Proj = Project;
        Smanager = scriptmanager;
    };
    void Update(float dt);
private:
    Logger* log = nullptr;
    project* Proj = nullptr;
    ScriptManager* Smanager = nullptr;
};
