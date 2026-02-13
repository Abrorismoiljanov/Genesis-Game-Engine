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
void Renderer::Render(project& Proj){
   glUseProgram(DefaultShader);

    glm::mat4 view = m_Camera.GetView();
    glm::mat4 projection = m_Camera.GetProjection();

    glUniformMatrix4fv(glGetUniformLocation(DefaultShader, "u_View"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(DefaultShader, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projection));

    if (Proj.SceneList.empty()) return;
    scene& activeScene = Proj.SceneList[0];

    for (uint32_t entityID : activeScene.EntityIDs)
    {
        entity* e = Proj.GetEntityByID(entityID);
        if (!e) continue;

        TransformComponent* transform = nullptr;
        MeshComponent* meshComp = nullptr;

        for (uint32_t cid : e->ComponentIDs)
        {
            Component* c = Proj.GetComponentByID(cid);
            if (!transform) transform = dynamic_cast<TransformComponent*>(c);
            if (!meshComp) meshComp = dynamic_cast<MeshComponent*>(c);
        }

        if (!transform || !meshComp) continue;

        glm::mat4 entityMatrix = transform->GetMatrix();

        glm::mat4 meshLocal =
            glm::translate(glm::mat4(1.0f), meshComp->transform.position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(meshComp->transform.rotation.x), glm::vec3(1,0,0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(meshComp->transform.rotation.y), glm::vec3(0,1,0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(meshComp->transform.rotation.z), glm::vec3(0,0,1)) *
            glm::scale(glm::mat4(1.0f), meshComp->transform.scale);

        glm::mat4 model = entityMatrix * meshLocal;

        glUniformMatrix4fv(glGetUniformLocation(DefaultShader, "u_Model"), 1, GL_FALSE, glm::value_ptr(model));

        for (auto& mesh : meshComp->meshes)
        {
            glBindVertexArray(mesh.VAO);
            glDrawElements(GL_TRIANGLES, mesh.IndexCount, GL_UNSIGNED_INT, 0);
        }
    }
}
