#include "Editor/include/Logger.h"
#include "DataTypes/project.h"

class CollisionSystem {
public:
    void Init(Logger* logger, project* Project){
        log = logger;
        Proj = Project;
    };
    void Update(float dt);
private:
    Logger* log = nullptr;
    project* Proj = nullptr;
};
