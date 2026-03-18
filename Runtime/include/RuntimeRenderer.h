#pragma once
#include "DataTypes/project.h"
#include "scene.h"
#include "GL/glew.h"
#include "Camera.h"
#include "Editor/include/Logger.h"

class RuntimeRenderer{

public:
    void Init(int w, int h, project& Proj, SDL_Window* window, Logger* Log);
    void BeginFrame(project& Proj, int selectedSceneID);
    void Render(project& Proj,int selectedSceneID);
    void EndFrame(SDL_Window* window);
    GCamera m_Camera;
    scene* activeScene = nullptr;
    entity* m_CameraEntity = nullptr;
    CameraComponent* m_CameraComponent = nullptr;

    std::unordered_map<TextureAsset*, GLuint> runtimeTextureIDs;
 
    float scale = 1.0f;
    glm::vec2 camPos = {0.0f, 0.0f};
    
private:
    GLuint DefaultShader;

    GLuint QuadVAO = 0;
    GLuint QuadVBO = 0;
    GLuint QuadEBO = 0;
};
