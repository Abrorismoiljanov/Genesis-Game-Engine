#pragma once
#include "components.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include "ImGuiFileDialog.h"
#include "GL/glew.h"

#include "Assets/MaterialAsset.h"
#include "transformcomponent.h"
#include "Assets/MeshAsset.h"

class MeshComponent: public Component{
public:

    std::vector<Mesh> meshes;
   TransformData transform;
    std::string MeshPath;


    std::string Getname(){
        return "Mesh";
    };
    
glm::mat4 GetMatrix() const {
    glm::mat4 T = glm::translate(glm::mat4(1.0f), transform.position);

    glm::mat4 Rx = glm::rotate(glm::mat4(1.0f),
                               glm::radians(transform.rotation.x),
                               glm::vec3(1,0,0));
    glm::mat4 Ry = glm::rotate(glm::mat4(1.0f),
                               glm::radians(transform.rotation.y),
                               glm::vec3(0,1,0));
    glm::mat4 Rz = glm::rotate(glm::mat4(1.0f),
                               glm::radians(transform.rotation.z),
                               glm::vec3(0,0,1));

    glm::mat4 S = glm::scale(glm::mat4(1.0f), transform.scale);

    return T * Rz * Ry * Rx * S;
}

void CreateTestCube()
{
    Mesh cube;


Vertex vertices[] = {
    // Front face (Z+)
    {{-0.5f,-0.5f, 0.5f},{0,0,1},{0,0}},
    {{ 0.5f,-0.5f, 0.5f},{0,0,1},{1,0}},
    {{ 0.5f, 0.5f, 0.5f},{0,0,1},{1,1}},
    {{-0.5f, 0.5f, 0.5f},{0,0,1},{0,1}},

    // Back face (Z-)
    {{-0.5f,-0.5f,-0.5f},{0,0,-1},{1,0}},
    {{-0.5f, 0.5f,-0.5f},{0,0,-1},{1,1}},
    {{ 0.5f, 0.5f,-0.5f},{0,0,-1},{0,1}},
    {{ 0.5f,-0.5f,-0.5f},{0,0,-1},{0,0}},

    // Left face (X-)
    {{-0.5f,-0.5f,-0.5f},{-1,0,0},{0,0}},
    {{-0.5f,-0.5f, 0.5f},{-1,0,0},{1,0}},
    {{-0.5f, 0.5f, 0.5f},{-1,0,0},{1,1}},
    {{-0.5f, 0.5f,-0.5f},{-1,0,0},{0,1}},

    // Right face (X+)
    {{ 0.5f,-0.5f,-0.5f},{1,0,0},{1,0}},
    {{ 0.5f, 0.5f,-0.5f},{1,0,0},{1,1}},
    {{ 0.5f, 0.5f, 0.5f},{1,0,0},{0,1}},
    {{ 0.5f,-0.5f, 0.5f},{1,0,0},{0,0}},

    // Top face (Y+)
    {{-0.5f, 0.5f,-0.5f},{0,1,0},{0,0}},
    {{-0.5f, 0.5f, 0.5f},{0,1,0},{0,1}},
    {{ 0.5f, 0.5f, 0.5f},{0,1,0},{1,1}},
    {{ 0.5f, 0.5f,-0.5f},{0,1,0},{1,0}},

    // Bottom face (Y-)
    {{-0.5f,-0.5f,-0.5f},{0,-1,0},{1,1}},
    {{ 0.5f,-0.5f,-0.5f},{0,-1,0},{0,1}},
    {{ 0.5f,-0.5f, 0.5f},{0,-1,0},{0,0}},
    {{-0.5f,-0.5f, 0.5f},{0,-1,0},{1,0}},
};

uint32_t indices[] = {
    // Front face
    0,1,2, 2,3,0,
    // Back face
    4,5,6, 6,7,4,
    // Left face
    8,9,10, 10,11,8,
    // Right face
    12,13,14, 14,15,12,
    // Top face
    16,17,18, 18,19,16,
    // Bottom face
    20,21,22, 22,23,20
};

    cube.vertices.assign(std::begin(vertices), std::end(vertices));
    cube.indices.assign(std::begin(indices), std::end(indices));
    cube.IndexCount = cube.indices.size();

    // Generate VAO/VBO/EBO
    glGenVertexArrays(1, &cube.VAO);
    glGenBuffers(1, &cube.VBO);
    glGenBuffers(1, &cube.EBO);

    glBindVertexArray(cube.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, cube.VBO);
    glBufferData(GL_ARRAY_BUFFER, cube.vertices.size() * sizeof(Vertex), cube.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indices.size() * sizeof(uint32_t), cube.indices.data(), GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)); // normal
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)); // uv
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    meshes.push_back(cube);
}



    void DrawComponentUI(){

        CreateTestCube();
        if (ImGui::Button("Load Mesh", ImVec2(0,30))) {
            IGFD::FileDialogConfig cfg;


            ImGuiFileDialog::Instance()->OpenDialog(
                "Choosef",
                "Choose File",
                ".obj,.glb,.gltf",
                cfg
            );
        }
        ImGui::SameLine();


        if (ImGuiFileDialog::Instance()->Display("Choosef"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
        MeshPath = ImGuiFileDialog::Instance()->GetFilePathName();
            }
            ImGuiFileDialog::Instance()->Close();
        }
        ImGui::BeginChild("MeshPathBox", ImVec2(0, 30), true); // true = frame 
        ImGui::Text("%s", MeshPath.c_str());
        ImGui::EndChild();

        ImGui::Separator();
    }

private:
    static uint32_t s_NextID;

    static uint32_t GenerateUniqueID() {
        return ++s_NextID;
    }
};
