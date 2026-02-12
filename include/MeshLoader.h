#pragma once
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "MeshComponent.h"
#include "Assets/MaterialAsset.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class MeshLoader {
public:
    static std::shared_ptr<MeshComponent> LoadMesh(const std::string& path);

private:
    static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, const std::string& directory);
    static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory);
    static MaterialData ProcessMaterial(aiMaterial* material, const std::string& directory);
};
