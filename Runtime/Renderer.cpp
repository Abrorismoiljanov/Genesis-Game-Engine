#include "GL/glew.h"
#include "ShaderUtils.h"
#include "FrameBuffer.h"
#include "RuntimeRenderer.h"
#include "transformcomponent.h"
#include "SpriteComponent.h"

void RuntimeRenderer::Init(int w, int h){

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    DefaultShader = CompileShader("/home/abror/Project/GGE/Shader/VSH.glsl","/home/abror/Project/GGE/Shader/FSH.glsl");
 
    float vertices[] = {
        -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &QuadVAO);
    glGenBuffers(1, &QuadVBO);
    glGenBuffers(1, &QuadEBO);

    glBindVertexArray(QuadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, QuadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // uv
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void RuntimeRenderer::BeginFrame(project& Proj, int selectedSceneID){
 
    for (auto& s : Proj.SceneList) {
        if (s.ID == selectedSceneID) {
            activeScene = &s;
            break;
        }
    }
    if (!activeScene) return;

    glViewport(0, 0, 1920, 1080); 
    glClearColor(activeScene->Param.BackgroundColor.r, 
                 activeScene->Param.BackgroundColor.g,
                 activeScene->Param.BackgroundColor.b,
                 activeScene->Param.BackgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void RuntimeRenderer::EndFrame(SDL_Window* window){
    SDL_GL_SwapWindow(window);
}
void RuntimeRenderer::Render(project& Proj, int selectedSceneID){

    glUseProgram(DefaultShader);

    float scale = m_Camera.Zoom; 

    m_Camera.Position.x = round(m_Camera.Position.x * scale) / scale;
    m_Camera.Position.y = round(m_Camera.Position.y * scale) / scale;

    glm::mat4 view = m_Camera.GetViewProjection();

    glUniformMatrix4fv(glGetUniformLocation(DefaultShader, "u_VP"), 1, GL_FALSE, glm::value_ptr(view));

    if (Proj.SceneList.empty()) return;



    for (uint32_t entityID : activeScene->EntityIDs){
   entity* e = Proj.GetEntityByID(entityID);
    if (!e) continue;



    glm::vec2 pos = e ? e->transform.position : glm::vec2(0.0f);
    float rot = e ? e->transform.rotation : 0.0f;
    glm::vec2 scale = e ? e->transform.scale : glm::vec2(1.0f);

    // Get SpriteComponent by ID
    SpriteComponent* sprite = nullptr;
    for (uint32_t compID : e->ComponentIDs) {
        Component* c = Proj.GetComponentByID(compID);
        if (!c) continue;

        if (c->Getname() == "Sprite") {
            sprite = static_cast<SpriteComponent*>(c);
            break;
        }
    }
    if (!sprite) continue;

        auto mat = Proj.Assets.Get<MaterialAsset>(sprite->materialHandle);

        if (!mat) continue;
        TextureAsset* tex = mat->GetTexture().get();
        if (!tex || tex->ID == 0) continue;

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(pos, 0.0f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0,0,1));
        model = glm::scale(model, glm::vec3(scale * sprite->size, 1.0f));

        glUniformMatrix4fv(glGetUniformLocation(DefaultShader, "u_Model"), 1, GL_FALSE, glm::value_ptr(model));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex->ID);
        glUniform1i(glGetUniformLocation(DefaultShader, "u_Texture"), 0);

        glBindVertexArray(QuadVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}
