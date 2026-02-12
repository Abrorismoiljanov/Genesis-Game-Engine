#pragma once
#include "project.h"
#include "scene.h"
#include "FrameBuffer.h"


class Renderer{

public:
    void Init(int w, int h);
    void BeginFrame(int w, int h);
    void Render(scene& scn, project& Proj);
    void EndFrame();

    uint32_t GetFinalImage() const { return m_Framebuffer.GetColorAttachment(); }

private:
    FrameBuffer m_Framebuffer;
};
