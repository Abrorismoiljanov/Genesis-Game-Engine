#include "MeshLoader.h"
#include "iostream"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

std::shared_ptr<MeshAsset> MeshLoader::Load(const std::string& path){

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_GenNormals |
                                             aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "I guess Model is broken or whatever, Gotta make a Console for Editor" << '\n';
        return nullptr;
    }

    auto meshAsset = std::make_shared<MeshAsset>();
    meshAsset->Path = path;


    for (unsigned int m = 0; m < scene->mNumMeshes; ++m){
        aiMesh* ai_mesh = scene->mMeshes[m];
        Mesh mesh;
 
        for (unsigned int i = 0; i < ai_mesh->mNumVertices; ++i){
            Vertex vertex;

            vertex.position = {
                ai_mesh->mVertices[i].x,
                ai_mesh->mVertices[i].y,
                ai_mesh->mVertices[i].z
            };
            if (ai_mesh->HasNormals()){
                vertex.normal = {
                    ai_mesh->mNormals[i].x,
                    ai_mesh->mNormals[i].y,
                    ai_mesh->mNormals[i].z
                };
            }else {
                vertex.normal = {0.0f, 0.0f, 0.0f};
            }
            if (ai_mesh->mTextureCoords[0])
    
            {
                vertex.uv = {
                    ai_mesh->mTextureCoords[0][i].x,
                    ai_mesh->mTextureCoords[0][i].y
                };
            }else{
                vertex.uv = {0.0f, 0.0f};
            }
            mesh.vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < ai_mesh->mNumFaces; ++i){
            aiFace face = ai_mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; ++j){
                mesh.indices.push_back(face.mIndices[j]);
            }
        }
        mesh.IndexCount = mesh.indices.size();

        glGenVertexArrays(1, &mesh.VAO);
        glGenBuffers(1, &mesh.VBO);
        glGenBuffers(1, &mesh.EBO);

        glBindVertexArray(mesh.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     mesh.vertices.size() * sizeof(Vertex),
                     mesh.vertices.data(),
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     mesh.indices.size() * sizeof(uint32_t),
                     mesh.indices.data(),
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
   
        meshAsset->meshes.push_back(std::move(mesh));
    }

    return meshAsset;
};
