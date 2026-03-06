#pragma once
#include "project.h"
#include "scene.h"
#include "FrameBuffer.h"
#include "GL/glew.h"
#include "ViewportCamera.h"

class Renderer{

public:
    void Init(int w, int h);
    void BeginFrame(project& Proj, int selectedSceneID);
    void Render(project& Proj,int selectedSceneID);
    void EndFrame();
    ViewportCamera m_Camera;
    scene* activeScene = nullptr;

    bool DrawGrid = true;
    bool DrawAxis = true;

    std::unordered_map<TextureAsset*, GLuint> editorTextureIDs;
    GLuint UploadTextureToGPU(TextureAsset* tex); 
    ImTextureID GetPreviewTextureID(TextureAsset* tex);

    void RenderGrid();
    void RenderAxis();
    void RenderCameraGizmos(project& Proj);
    
    uint32_t GetFinalImage() const { return m_Framebuffer.GetColorAttachment(); }

private:
    FrameBuffer m_Framebuffer;
    GLuint DefaultShader;
    GLuint GridShader;


    GLuint QuadVAO = 0;
    GLuint QuadVBO = 0;
    GLuint QuadEBO = 0;
};
