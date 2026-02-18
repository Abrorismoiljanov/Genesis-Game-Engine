#include "GL/glew.h"
#include "ShaderUtils.h"
#include "FrameBuffer.h"
#include "Renderer.h"
#include "transformcomponent.h"
#include "MeshComponent.h"

void Renderer::Init(int w, int h){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

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
void Renderer::Render(project& Proj){
   glUseProgram(DefaultShader);

    glm::mat4 view = m_Camera.GetView();
    glm::mat4 projection = m_Camera.GetProjection();

    glUniformMatrix4fv(glGetUniformLocation(DefaultShader, "u_View"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(DefaultShader, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projection));

    if (Proj.SceneList.empty()) return;
    scene& activeScene = Proj.SceneList[0];

    for (uint32_t entityID : activeScene.EntityIDs){
        entity* e = Proj.GetEntityByID(entityID);
        if (!e) continue;
 

    }
}
