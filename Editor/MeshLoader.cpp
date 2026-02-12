#include "assimp/Importer.hpp"
#include "MeshLoader.h"
#include "Assets/MaterialAsset.h"

std::shared_ptr<MeshComponent> MeshLoader::LoadMesh(const std::string &path){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);

    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
    {
        std::cerr << "Assimp Error: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    std::string directory = path.substr(0, path.find_last_of('/'));

    std::vector<Mesh> meshes;

    ProcessNode(scene->mRootNode, scene, meshes, directory);

    auto meshComp = std::make_shared<MeshComponent>();
    meshComp->meshes = std::move(meshes);
    meshComp->MeshPath = path;

    return meshComp;
};



void MeshLoader::ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, const std::string& directory){
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene, directory));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene, meshes, directory);
    }
};

Mesh MeshLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory){

Mesh outMesh;

for (unsigned int i = 0; i < mesh->mNumVertices; i++)
{
    Vertex vertex;

    vertex.position = {
        mesh->mVertices[i].x,
        mesh->mVertices[i].y,
        mesh->mVertices[i].z
    };

    if (mesh->HasNormals())
    {
        vertex.normal = {
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        };
    }

    if (mesh->mTextureCoords[0])
    {
        vertex.uv = {
            mesh->mTextureCoords[0][i].x,
            mesh->mTextureCoords[0][i].y
        };
    }
    outMesh.vertices.push_back(vertex);
    }


    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
    aiFace face = mesh->mFaces[i];

    for (unsigned int j = 0; j < face.mNumIndices; j++)
    {
        outMesh.indices.push_back(face.mIndices[j]);
    }
    }

if (mesh->mMaterialIndex >= 0){
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    outMesh.Mat = ProcessMaterial(material, directory);
    }
    return outMesh;
};

MaterialData MeshLoader::ProcessMaterial(aiMaterial* material, const std::string& directory){

    MaterialData mat;

    aiColor3D color;

    if (material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
        mat.albedo = glm::vec4(color.r, color.g, color.b, 1.0f);


    if (material->Get(AI_MATKEY_COLOR_EMISSIVE, color) == AI_SUCCESS)
        mat.emissiveIntensity = (color.r + color.g + color.b) / 3.0f; 


    float metallic = 0.0f;
    if (material->Get(AI_MATKEY_METALLIC_FACTOR, metallic) == AI_SUCCESS)
        mat.metallic = metallic;

    float roughness = 1.0f;
    if (material->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness) == AI_SUCCESS)
        mat.roughness = roughness;


aiString str;
if (material->GetTexture(aiTextureType_DIFFUSE, 0, &str) == AI_SUCCESS)
    mat.albedoTexturePath = directory + "/" + std::string(str.C_Str());
if (material->GetTexture(aiTextureType_NORMALS, 0, &str) == AI_SUCCESS)
    mat.normalTexturePath = directory + "/" + std::string(str.C_Str());
if (material->GetTexture(aiTextureType_METALNESS, 0, &str) == AI_SUCCESS)
    mat.metallicTexturePath = directory + "/" + std::string(str.C_Str());
if (material->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &str) == AI_SUCCESS)
    mat.roughnessTexturePath = directory + "/" + std::string(str.C_Str());
if (material->GetTexture(aiTextureType_EMISSIVE, 0, &str) == AI_SUCCESS)
    mat.emissiveTexturePath = directory + "/" + std::string(str.C_Str());

    return mat;

};




