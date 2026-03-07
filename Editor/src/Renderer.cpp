#include "GL/glew.h"
#include "DataTypes/outside/ShaderUtils.h"
#include "Editor/include/FrameBuffer.h"
#include "Editor/include/Renderer.h"
#include "DataTypes/Components/SpriteComponent.h"

void Renderer::Init(int w, int h){

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    DefaultShader = CompileShader("/home/abror/Project/GGE/Shader/VSH.glsl","/home/abror/Project/GGE/Shader/FSH.glsl");
    GridShader = CompileShader("/home/abror/Project/GGE/Shader/GridVert.glsl","/home/abror/Project/GGE/Shader/GridFrag.glsl");
 
    m_Framebuffer.Create(w, h);

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

void Renderer::BeginFrame(project& Proj, int selectedSceneID){
 
    for (auto& s : Proj.SceneList) {
        if (s.ID == selectedSceneID) {
            activeScene = &s;
            break;
        }
    }
    if (!activeScene) return;

    m_Framebuffer.Bind();

    glViewport(0, 0, m_Framebuffer.m_Width, m_Framebuffer.m_Height); 
    glClearColor(activeScene->Param.BackgroundColor.r, 
                 activeScene->Param.BackgroundColor.g,
                 activeScene->Param.BackgroundColor.b,
                 activeScene->Param.BackgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 
    for (auto& comp_ptr : Proj.ComponentList) {
        if (comp_ptr->Getname() != "Sprite") continue;
        SpriteComponent* sprite = static_cast<SpriteComponent*>(comp_ptr.get());
        std::cout << sprite->Getname() << " was Loaded" << '\n';

        auto mat = Proj.Assets.Get<MaterialAsset>(sprite->materialHandle);
        if (!mat) continue;
        std::cout << mat->GetTexture()->Path << " was Loaded" << '\n';

        TextureAsset* tex = mat->GetTexture().get();

        if (editorTextureIDs.find(tex) == editorTextureIDs.end()) {
            if (!tex->LoadFromFile(tex->Path)) {
                std::cout << "FAILED to load texture: " << tex->Path << "\n";
                continue;
            }

            GLuint texID;
            glGenTextures(1, &texID);
            glBindTexture(GL_TEXTURE_2D, texID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels.data());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);

            editorTextureIDs[tex] = texID;

            tex->pixels.clear();
        }
    }
}
void Renderer::EndFrame(){
    m_Framebuffer.UnBind();
}
void Renderer::Render(project& Proj, int selectedSceneID){

    for (auto& [texPtr, texID] : editorTextureIDs) {
        std::cout << "[Renderer] Texture ptr: " << texPtr << " ID: " << texID << "\n";
    }
 
    if (DrawGrid) {
        RenderGrid();
    }
    if (DrawAxis) {
        RenderAxis();
    }

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


        SpriteComponent* sprite = nullptr;
        CameraComponent* cam = nullptr;
 
        for (uint32_t compID : e->ComponentIDs) {
            Component* c = Proj.GetComponentByID(compID);
            if (!c) continue;
            if (c->Getname() == "Sprite") {
                sprite = static_cast<SpriteComponent*>(c);
            }
        }
        if (!sprite) continue;

        auto mat = Proj.Assets.Get<MaterialAsset>(sprite->materialHandle);

        if (!mat) continue;
        TextureAsset* tex = mat->GetTexture().get();
        if (!tex) continue;

        GLuint texID = editorTextureIDs[tex];
 
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(pos, 0.0f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0,0,1));
        model = glm::scale(model, glm::vec3(scale * sprite->size, 1.0f));

        glUniformMatrix4fv(glGetUniformLocation(DefaultShader, "u_Model"), 1, GL_FALSE, glm::value_ptr(model));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texID);
        glUniform1i(glGetUniformLocation(DefaultShader, "u_Texture"), 0);

        glBindVertexArray(QuadVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    RenderCameraGizmos(Proj);
}

void Renderer::RenderCameraGizmos(project& Proj){
    glUseProgram(GridShader);

    glm::mat4 vp = m_Camera.GetViewProjection();
    glUniformMatrix4fv(
        glGetUniformLocation(GridShader, "u_VP"),
        1, GL_FALSE,
        glm::value_ptr(vp)
    );

    float aspect = (float)Proj.Param.Resolution.width / Proj.Param.Resolution.height;

    float worldHeight = 1.0f / m_Camera.Zoom; 
    float worldWidth  = worldHeight * aspect;

    for (uint32_t entityID : activeScene->EntityIDs)
    {
        entity* e = Proj.GetEntityByID(entityID);
        if (!e) continue;

        CameraComponent* cam = nullptr;

        for (uint32_t compID : e->ComponentIDs)
        {
            Component* c = Proj.GetComponentByID(compID);
            if (c && c->Getname() == "Camera")
                cam = static_cast<CameraComponent*>(c);
        }

        if (!cam) continue;

        float halfHeight = Proj.Param.Resolution.height * 0.5f / cam->Zoom;
        float halfWidth  = halfHeight * aspect;

        glm::vec2 pos = e->transform.position;
        float rot = e->transform.rotation;

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(pos, 0.0f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0,0,1));

        glm::vec4 corners[4] = {
            model * glm::vec4(-halfWidth, -halfHeight, 0, 1),
            model * glm::vec4( halfWidth, -halfHeight, 0, 1),
            model * glm::vec4( halfWidth,  halfHeight, 0, 1),
            model * glm::vec4(-halfWidth,  halfHeight, 0, 1)
        };

        float vertices[] = {
            corners[0].x, corners[0].y,
            corners[1].x, corners[1].y,

            corners[1].x, corners[1].y,
            corners[2].x, corners[2].y,

            corners[2].x, corners[2].y,
            corners[3].x, corners[3].y,

            corners[3].x, corners[3].y,
            corners[0].x, corners[0].y,
        };

        GLuint vbo, vao;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glUniform4f(
            glGetUniformLocation(GridShader, "u_Color"),
            0.5f, 0.5f, 1.0f, 1.0f
        );
 
        glLineWidth(3.0f);
        glDrawArrays(GL_LINES, 0, 8);
        glLineWidth(1.0f);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
}

void Renderer::RenderAxis(){
glUseProgram(GridShader);

    glm::vec2 camPos = m_Camera.Position;
    float zoom = m_Camera.Zoom;

    // Viewport bounds in world units
    float halfWidth  = m_Framebuffer.m_Width  / (2.0f * zoom);
    float halfHeight = m_Framebuffer.m_Height / (2.0f * zoom);

    float left   = camPos.x - halfWidth;
    float right  = camPos.x + halfWidth;
    float bottom = camPos.y - halfHeight;
    float top    = camPos.y + halfHeight;

    // Axis lines vertices
    float vertices[] = {
        // X axis
        left, 0.0f,
        right, 0.0f,

        // Y axis
        0.0f, bottom,
        0.0f, top
    };

    GLuint axisVBO, axisVAO;
    glGenVertexArrays(1, &axisVAO);
    glGenBuffers(1, &axisVBO);

    glBindVertexArray(axisVAO);
    glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glLineWidth(2.0f); 
    glUniformMatrix4fv(glGetUniformLocation(GridShader, "u_VP"), 1, GL_FALSE, glm::value_ptr(m_Camera.GetViewProjection()));
    
    // X axis
    glUniform4f(glGetUniformLocation(GridShader, "u_Color"), 1.0f, 0.0f, 0.0f, 1.0f); 
    glDrawArrays(GL_LINES, 0, 2);

    // Y axis
    glUniform4f(glGetUniformLocation(GridShader, "u_Color"), 0.0f, 1.0f, 0.0f, 1.0f);
    glDrawArrays(GL_LINES, 2, 2);

    glLineWidth(1.0f);  
    glBindVertexArray(0);
    glDeleteBuffers(1, &axisVBO);
    glDeleteVertexArrays(1, &axisVAO);
}

void Renderer::RenderGrid(){
    glUseProgram(GridShader);

    glm::mat4 viewProj = m_Camera.GetViewProjection();
    glUniformMatrix4fv(glGetUniformLocation(GridShader, "u_VP"), 1, GL_FALSE, glm::value_ptr(viewProj));
    glUniform4f(glGetUniformLocation(GridShader, "u_Color"), 0.3f, 0.3f, 0.3f, 1.0f);

    float pixelsPerUnit = 100.0f;

    float gridSpacing = pixelsPerUnit / m_Camera.Zoom; 
    // Get camera info
    glm::vec2 camPos = m_Camera.Position;
    float zoom = m_Camera.Zoom;

    // Viewport size in world units
    float width  = m_Framebuffer.m_Width  / zoom;
    float height = m_Framebuffer.m_Height / zoom;

    float left   = m_Camera.Position.x - (m_Framebuffer.m_Width  / 2.0f) / m_Camera.Zoom;
    float right  = m_Camera.Position.x + (m_Framebuffer.m_Width  / 2.0f) / m_Camera.Zoom;
    float bottom = m_Camera.Position.y - (m_Framebuffer.m_Height / 2.0f) / m_Camera.Zoom;
    float top    = m_Camera.Position.y + (m_Framebuffer.m_Height / 2.0f) / m_Camera.Zoom;
 
    std::vector<float> vertices;

    float worldSpacing = 100.0f;

    for (float x = floor(left / worldSpacing) * worldSpacing; x <= right; x += worldSpacing){
        vertices.push_back(x); vertices.push_back(bottom);
        vertices.push_back(x); vertices.push_back(top);
    }

    for (float y = floor(bottom / worldSpacing) * worldSpacing; y <= top; y += worldSpacing){
        vertices.push_back(left); vertices.push_back(y);
        vertices.push_back(right); vertices.push_back(y);
    }

    // Upload to GPU
    GLuint gridVBO, gridVAO;
    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);

    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, (GLsizei)(vertices.size() / 2));

    glBindVertexArray(0);
    glDeleteBuffers(1, &gridVBO);
    glDeleteVertexArrays(1, &gridVAO);
}

GLuint Renderer::UploadTextureToGPU(TextureAsset* tex) {
    if (!tex) return 0;
 
    auto it = editorTextureIDs.find(tex);
    if (it != editorTextureIDs.end() && it->second != 0) {
        glDeleteTextures(1, &it->second); 
    }

    if (!tex->pixels.size() && !tex->LoadFromFile(tex->Path)) {
        return 0;
    }


    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->Width, tex->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    editorTextureIDs[tex] = texID;

    tex->pixels.clear();

    return texID;
}
ImTextureID Renderer::GetPreviewTextureID(TextureAsset* tex) {
    if (!tex) return 0;

    auto it = editorTextureIDs.find(tex);
    if (it != editorTextureIDs.end())
        return (ImTextureID)(uintptr_t)it->second;

    return 0;
}
