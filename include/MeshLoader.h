#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "Assets/MeshAsset.h"
#include "memory"

class MeshLoader{    
public:
    std::shared_ptr<MeshAsset> Load(const std::string& path);
};
