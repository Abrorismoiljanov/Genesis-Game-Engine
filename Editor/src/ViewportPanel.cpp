#include "Editor/include/Panels.h"

bool findinScene(scene* activeScene,  entity* CurrentEntity){
    if (!activeScene || !CurrentEntity)
        return false;
    for (auto& e: activeScene->EntityIDs) {
        if (e == CurrentEntity->ID) {
            return true;
        }
    } 
    return false;
};

void ApplyMatrixTo2D(entity* e, const glm::mat4& mat){
    // Translation
    e->transform.position.x = mat[3][0];
    e->transform.position.y = mat[3][1];

    // Scale (length of basis vectors)
    e->transform.scale.x = glm::length(glm::vec2(mat[0]));
    e->transform.scale.y = glm::length(glm::vec2(mat[1]));

    // Rotation (extract from normalized X axis)
    glm::vec2 right = glm::normalize(glm::vec2(mat[0]));
    float angle = atan2(right.y, right.x);
    e->transform.rotation = glm::degrees(angle);
}



void Viewport::Render(){
    
    entity* CurrentEntity = nullptr;
    uint32_t selectedID = selection.EntityID;
    scene* activeScene = Proj.GetSceneByID(SelectedScene);

    bool ValidScene = (activeScene != nullptr);
    
    for (auto& SelectedE : Proj.EntityList) {
        if (selection.EntityID == SelectedE.ID) {
            CurrentEntity = &SelectedE;
        }
    }; 

    ImGui::Begin("Viewport");
    
    if (activeScene) {
        ValidScene = true;
    }else {
        ValidScene = false;
    }
    if (!ValidScene) {
        ImGui::Text("Please Select a Scene");
    }
    if (ValidScene) {

        ImVec2 size = ImGui::GetContentRegionAvail();

        m_renderer->m_Camera.SetViewportSize(size.x, size.y);
 
        uint32_t tex = m_renderer->GetFinalImage();
  

        ImGui::Image(
            (ImTextureID)(uintptr_t)tex,
            size,
            ImVec2(0,1),
            ImVec2(1,0));

   
        bool hovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
        bool rmbPressed = ImGui::IsMouseDown(ImGuiMouseButton_Right);
 

        bool imageHovered = ImGui::IsItemHovered();

        ImVec2 mousePos = ImGui::GetMousePos();
        ImVec2 imageMin = ImGui::GetItemRectMin();
        ImVec2 imageMax = ImGui::GetItemRectMax();
 
        bool overGizmo = ImGuizmo::IsOver();
 
        glm::vec2 localMouse = {

            mousePos.x - imageMin.x,
            imageMax.y - mousePos.y // Y flipped here to match framebuffer
        };

        bool rmb = ImGui::IsMouseDown(ImGuiMouseButton_Right);

        if (imageHovered && rmb && !overGizmo){
            if (!m_CapturingMouse){
                m_CapturingMouse = true;
                m_LastMousePos = mousePos;
            }

            float dx = mousePos.x - m_LastMousePos.x;
            float dy = mousePos.y - m_LastMousePos.y;
 
            m_LastMousePos = mousePos;
            m_renderer->m_Camera.ProcessMousePan(dx, dy);
        }else{
            m_CapturingMouse = false;
        }

        if (imageHovered){
            float scroll = ImGui::GetIO().MouseWheel;
            if (scroll != 0.0f)
            {
                m_renderer->m_Camera.ProcessScroll(scroll, localMouse);
            }
        }

        bool DrawGizmo = false;
        if (CurrentEntity && activeScene && findinScene(activeScene, CurrentEntity)){
            DrawGizmo = true;
        }

        if (DrawGizmo){
            ImGuizmo::BeginFrame();
    
            ImGuizmo::SetOrthographic(true); 
            ImGuizmo::SetDrawlist();

            ImVec2 imageSize = ImGui::GetItemRectSize();

            ImGuizmo::SetRect(imageMin.x, imageMin.y, imageMax.x - imageMin.x, imageMax.y - imageMin.y);

            glm::mat4 view = m_renderer->m_Camera.GetViewMatrix();
            glm::mat4 proj = m_renderer->m_Camera.GetProjectionMatrix();

            glm::mat4 transform = CurrentEntity->GetTransformMatrix();
            ImGuizmo::SetGizmoSizeClipSpace(0.2f);


            ImGuizmo::Enable(true);

            ImGuizmo::Manipulate(
                glm::value_ptr(-view),
                glm::value_ptr(proj),
                mode,   
                ImGuizmo::LOCAL,
                glm::value_ptr(transform)
            );

            if (ImGuizmo::IsUsing()){
                ApplyMatrixTo2D(CurrentEntity, transform);
            }
        }
 
        ImGui::SetCursorPos(ImVec2(10, 30)); 

        if (ImGui::Button(ICON_FA_ARROWS_UP_DOWN_LEFT_RIGHT)) {
            mode = ImGuizmo::TRANSLATE;
        }
     ImGui::SameLine();
        if (ImGui::Button(ICON_FA_ROTATE)) {
            mode = ImGuizmo::ROTATE_Z;
        }  
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_UP_RIGHT_AND_DOWN_LEFT_FROM_CENTER)) {
            mode = ImGuizmo::SCALE;
        }

        ImGui::SameLine();
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImGui::SetCursorPosX(windowSize.x - 220);

        ImGui::Checkbox("Grid", &m_renderer->DrawGrid);

        ImGui::SameLine();
        
        ImGui::Checkbox("Axis", &m_renderer->DrawAxis);
    
        ImGui::SameLine();

        const char* label = Runtime.isRunning() ? ICON_FA_STOP " Stop" : ICON_FA_PLAY " Start";

        if (ImGui::Button(label)) {
            if (Runtime.isRunning()) {
                Runtime.Stop();
            } else {
                Runtime.Start(Proj);
            }
        }
        float fps = (deltatime > 0.0f) ? (1.0f / deltatime) : 0.0f;
        ImGui::Text("FPS: %.1f", fps);
        ImGui::Text("Zoom: %.1f", m_renderer->m_Camera.Zoom);
    }
        
    ImGui::End();
}
void Viewport::Update(float dt){
    deltatime = dt; 
}

