#pragma once
#include "project.h"
#include "scene.h"
#include "FrameBuffer.h"
#include "GL/glew.h"
#include "ViewportCamera.h"

class RuntimeRenderer{

public:
    void Init(int w, int h);
    void BeginFrame(project& Proj, int selectedSceneID);
    void Render(project& Proj,int selectedSceneID);
    void EndFrame(SDL_Window* window);
    ViewportCamera m_Camera;
    scene* activeScene = nullptr;

private:
    GLuint DefaultShader;

    GLuint QuadVAO = 0;
    GLuint QuadVBO = 0;
    GLuint QuadEBO = 0;
};
