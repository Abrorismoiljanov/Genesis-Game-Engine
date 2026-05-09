#include "GL/glew.h"
#include "Runtime/include/RuntimeRenderer.h"
#include "DataTypes/Components/SpriteComponent.h"
#include "DataTypes/outside/ShaderUtils.h"

void RuntimeRenderer::Init(int w, int h, project& Proj, SDL_Window* window, Logger* Log){

    SDL_GL_GetDrawableSize(window, &Proj.Param.Resolution.width, &Proj.Param.Resolution.height);
    glViewport(0, 0, w, h);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    DefaultShader = CompileShader("Shader/VSH.glsl","Shader/FSH.glsl");
    DebugShader = CompileShader("Shader/GridVert.glsl","Shader/GridFrag.glsl");
    
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
    for (auto& [tex, id] : runtimeTextureIDs) {
        if (id != 0) {
            glDeleteTextures(1, &id);
        }
    }

    runtimeTextureIDs.clear(); 
    for (auto& comp_ptr : Proj.ComponentList) {
        if (comp_ptr->Getname() != "Sprite") continue;
        SpriteComponent* sprite = static_cast<SpriteComponent*>(comp_ptr.get());
        std::string msg = sprite->Getname() + " was Loaded";
        Log->Info(LogSystem::Renderer, msg);

        auto mat = Proj.Assets.Get<MaterialAsset>(sprite->materialHandle);
        if (!mat) continue;
        msg =  mat->GetTexture()->Path + " was Loaded";
        Log->Info(LogSystem::Renderer, msg);

        TextureAsset* tex = mat->GetTexture().get();

        if (runtimeTextureIDs.find(tex) == runtimeTextureIDs.end()) {
            if (!tex->LoadFromFile(tex->Path)) {
                msg =  "Failed to Load texture" + tex->Path;
                Log->Error(LogSystem::Renderer, msg);
                continue;
            }

            GLuint texID;
            glGenTextures(1, &texID);
            glBindTexture(GL_TEXTURE_2D, texID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels.data());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);

            runtimeTextureIDs[tex] = texID;

            tex->pixels.clear();

        }
    }
    m_Camera.SetViewportSize(Proj.Param.Resolution.width, Proj.Param.Resolution.height);
}

void RuntimeRenderer::BeginFrame(project& Proj, int selectedSceneID){
 
    activeScene = Proj.GetSceneByID(selectedSceneID);
    if (!activeScene) return;

    glClearColor(activeScene->Param.BackgroundColor.r, 
                 activeScene->Param.BackgroundColor.g,
                 activeScene->Param.BackgroundColor.b,
                 activeScene->Param.BackgroundColor.a);
    
    glClear(GL_COLOR_BUFFER_BIT);
 
    if (Proj.GetEntityByID(activeScene->Camera)) {
        m_CameraEntity = Proj.GetEntityByID(activeScene->Camera);
        m_CameraComponent = nullptr;

        if (m_CameraEntity) {
            for (uint32_t cid : m_CameraEntity->ComponentIDs) {
                Component* c = Proj.GetComponentByID(cid);
                if (!c) continue;

                if (c->Getname() == "Camera") {
                    m_CameraComponent = static_cast<CameraComponent*>(c);
                    break;
                }
            }
        }
    } else {
        m_CameraEntity = nullptr;
        m_CameraComponent = nullptr;
    }
}
void RuntimeRenderer::EndFrame(SDL_Window* window){
    SDL_GL_SwapWindow(window);
}
void RuntimeRenderer::Render(project& Proj, int selectedSceneID){
    if (!activeScene)
        activeScene = Proj.GetSceneByID(selectedSceneID);

    if (!activeScene)
        return;
    glUseProgram(DefaultShader);

    
    if (m_CameraEntity != nullptr){
        scale = m_CameraComponent->Zoom;
        m_Camera.Zoom = m_CameraComponent->Zoom;
        camPos.x = m_CameraEntity->transform.position.x;
        camPos.y = m_CameraEntity->transform.position.y;
  
        m_Camera.Position.x = round(m_CameraEntity->transform.position.x * scale) / scale;
        m_Camera.Position.y = round(m_CameraEntity->transform.position.y * scale) / scale;
    }

    glm::mat4 view = m_Camera.GetViewProjection();

    glUniformMatrix4fv(glGetUniformLocation(DefaultShader, "u_VP"), 1, GL_FALSE, glm::value_ptr(view));

    if (Proj.SceneList.empty()) return;



    for (uint32_t entityID : activeScene->EntityIDs){
        entity* e = Proj.GetEntityByID(entityID);
        if (!e) continue;

        glm::vec2 pos = e ? e->transform.position : glm::vec2(0.0f);
        float rot = e ? e->transform.rotation : 0.0f;
        glm::vec2 scale = e ? e->transform.scale : glm::vec2(1.0f);

    
        SpriteComponent* sprite = nullptr;
         for (uint32_t compID : e->ComponentIDs) {
            Component* c = Proj.GetComponentByID(compID);
            if (!c) continue;
            if (c->Getname() == "Sprite") {
                SpriteComponent* sprite = static_cast<SpriteComponent*>(c);

                auto mat = Proj.Assets.Get<MaterialAsset>(sprite->materialHandle);
                if (!mat) continue;
                TextureAsset* tex = mat->GetTexture().get();
                if (!tex) continue;
                GLuint texID = runtimeTextureIDs[tex];

                glm::mat4 model(1.0f);
                model = glm::translate(model, glm::vec3(pos, 0.0f));
                model = glm::rotate(model, glm::radians(rot), glm::vec3(0,0,1));
                model = glm::translate(model, glm::vec3(sprite->offset, 0.0f));

                model = glm::scale(model, glm::vec3(scale * sprite->size, 1.0f));
                
                glUniformMatrix4fv(glGetUniformLocation(DefaultShader, "u_Model"), 1, GL_FALSE, glm::value_ptr(model));
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texID);
                glUniform1i(glGetUniformLocation(DefaultShader, "u_Texture"), 0);

                glBindVertexArray(QuadVAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
            }
        }
    }
     
    if (Proj.Param.Debug) {
        RenderColliders(Proj);
    }
}
void RuntimeRenderer::RenderColliders(project& Proj) {
    glUseProgram(DebugShader); 
    glm::mat4 vp = m_Camera.GetViewProjection();
    glUniformMatrix4fv(glGetUniformLocation(DebugShader, "u_VP"), 1, GL_FALSE, glm::value_ptr(vp));

    for (uint32_t entityID : activeScene->EntityIDs) {
        entity* e = Proj.GetEntityByID(entityID);
        if (!e) continue;

        for (uint32_t compID : e->ComponentIDs) {
            Component* c = Proj.GetComponentByID(compID);
            if (!c || c->Getname() != "Collision") continue;

            CollisionComponent* col = static_cast<CollisionComponent*>(c);

            glm::vec2 center = glm::vec2(e->transform.position + col->offset);
            glm::vec2 half   = glm::vec2(col->halfSize.x * e->transform.scale.x,
                                         col->halfSize.y * e->transform.scale.y);

            // Rectangle corners
            glm::vec2 topLeft     = center + glm::vec2(-half.x,  half.y);
            glm::vec2 topRight    = center + glm::vec2( half.x,  half.y);
            glm::vec2 bottomRight = center + glm::vec2( half.x, -half.y);
            glm::vec2 bottomLeft  = center + glm::vec2(-half.x, -half.y);

            // Vertex data for a filled quad (two triangles)
            float vertices[] = {
                topLeft.x,    topLeft.y,
                bottomLeft.x, bottomLeft.y,
                bottomRight.x, bottomRight.y,

                bottomRight.x, bottomRight.y,
                topRight.x,    topRight.y,
                topLeft.x,     topLeft.y
            };

            GLuint vao, vbo;
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // Blue with 0.5 alpha
            glUniform4f(glGetUniformLocation(DebugShader, "u_Color"), 0.0f, 0.0f, 1.0f, 0.5f);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // Optional: outline
            float outlineVertices[] = {
                topLeft.x, topLeft.y, topRight.x, topRight.y,
                topRight.x, topRight.y, bottomRight.x, bottomRight.y,
                bottomRight.x, bottomRight.y, bottomLeft.x, bottomLeft.y,
                bottomLeft.x, bottomLeft.y, topLeft.x, topLeft.y
            };
            glBufferData(GL_ARRAY_BUFFER, sizeof(outlineVertices), outlineVertices, GL_DYNAMIC_DRAW);
            glUniform4f(glGetUniformLocation(DebugShader, "u_Color"), 0.0f, 0.0f, 1.0f, 1.0f);
            glLineWidth(2.0f);
            glDrawArrays(GL_LINES, 0, 8);
            glLineWidth(1.0f);

            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);
        }
    }
}

