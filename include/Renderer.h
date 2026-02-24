#pragma once
#include "project.h"
#include "scene.h"
#include "FrameBuffer.h"
#include "GL/glew.h"
#include "ViewportCamera.h"

class Renderer{

public:
    void Init(int w, int h);
    void BeginFrame(int w, int h);
    void Render(project& Proj);
    void EndFrame();
    ViewportCamera m_Camera;


    void RenderGrid();

    uint32_t GetFinalImage() const { return m_Framebuffer.GetColorAttachment(); }

private:
    FrameBuffer m_Framebuffer;
    GLuint DefaultShader;
    GLuint GridShader;


    GLuint QuadVAO = 0;
    GLuint QuadVBO = 0;
    GLuint QuadEBO = 0;
};
