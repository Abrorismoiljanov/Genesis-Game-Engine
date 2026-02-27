#include "GL/glew.h"
#include "ShaderUtils.h"
#include "FrameBuffer.h"
#include "Renderer.h"
#include "transformcomponent.h"
#include "SpriteComponent.h"

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

}
void Renderer::EndFrame(){
    m_Framebuffer.UnBind();
}
void Renderer::Render(project& Proj, int selectedSceneID){
 
    RenderGrid();
    RenderAxis();

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

    // Set uniform: axes color (red for X, green for Y if you want)
    glUniformMatrix4fv(glGetUniformLocation(GridShader, "u_VP"), 1, GL_FALSE, glm::value_ptr(m_Camera.GetViewProjection()));
    
    // X axis
    glUniform4f(glGetUniformLocation(GridShader, "u_Color"), 1.0f, 0.0f, 0.0f, 1.0f); 
    glDrawArrays(GL_LINES, 0, 2);

    // Y axis
    glUniform4f(glGetUniformLocation(GridShader, "u_Color"), 0.0f, 1.0f, 0.0f, 1.0f);
    glDrawArrays(GL_LINES, 2, 2);

    glBindVertexArray(0);
    glDeleteBuffers(1, &axisVBO);
    glDeleteVertexArrays(1, &axisVAO);
}

void Renderer::RenderGrid(){
    glUseProgram(GridShader);

    glm::mat4 viewProj = m_Camera.GetViewProjection();
    glUniformMatrix4fv(glGetUniformLocation(GridShader, "u_VP"), 1, GL_FALSE, glm::value_ptr(viewProj));
    glUniform4f(glGetUniformLocation(GridShader, "u_Color"), 0.3f, 0.3f, 0.3f, 1.0f);

    float gridSpacing = 50.0f; 
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

    float worldSpacing = gridSpacing / m_Camera.Zoom;

for (float x = floor(left / worldSpacing) * worldSpacing; x <= right; x += worldSpacing)
{
    vertices.push_back(x); vertices.push_back(bottom);
    vertices.push_back(x); vertices.push_back(top);
}

for (float y = floor(bottom / worldSpacing) * worldSpacing; y <= top; y += worldSpacing)
{
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
