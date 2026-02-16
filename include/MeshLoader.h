#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "Assets/ModelAsset.h"
#include "Assets/MaterialAsset.h"
#include "memory"

class MeshLoader{    
public:
    std::shared_ptr<ModelAsset> Load(const std::string& path);
    std::vector<std::shared_ptr<MaterialAsset>> MateriaLoad(const std::string& path);
};
