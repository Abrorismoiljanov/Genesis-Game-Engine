#pragma once
#include "project.h"
#include "scene.h"
#include "FrameBuffer.h"
#include "GL/glew.h"
#include "ViewportCamera.h"

class RuntimeRenderer{

public:
    void Init(int w, int h);
    void BeginFrame();
    void Render(project& Proj);
    void EndFrame();
    ViewportCamera m_Camera;

private:
    int Width;
    int Height;
    GLuint DefaultShader;


    GLuint QuadVAO = 0;
    GLuint QuadVBO = 0;
    GLuint QuadEBO = 0;
};
