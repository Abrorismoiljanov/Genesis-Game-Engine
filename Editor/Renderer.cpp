#include "GL/glew.h"
#include "ShaderUtils.h"
#include "FrameBuffer.h"
#include "Renderer.h"
#include "transformcomponent.h"
#include "MeshComponent.h"


void Renderer::Init(int w, int h){
    glEnable(GL_DEPTH_TEST);

    DefaultShader = CompileShader("/home/abror/Project/GGE/Shader/VSH.glsl","/home/abror/Project/GGE/Shader/FSH.glsl");
    m_Framebuffer.Create(w, h);
}

void Renderer::BeginFrame(int w, int h){

    m_Framebuffer.Bind();

    glViewport(0, 0, w, h); 
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void Renderer::EndFrame(){
    m_Framebuffer.UnBind();
}
void Renderer::Render(scene& scn, project& Proj){

}
