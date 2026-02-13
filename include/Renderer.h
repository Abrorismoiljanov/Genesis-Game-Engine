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

    uint32_t GetFinalImage() const { return m_Framebuffer.GetColorAttachment(); }

private:
    FrameBuffer m_Framebuffer;
    GLuint DefaultShader;
};
