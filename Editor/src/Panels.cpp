#include "Editor/include/Panels.h"
#include "imgui.h"
#include "project.h"
#include "Editor/include/CompRegister.h"
#include "ImGuizmo.h"

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


void Terminal::Render(){
    ImGui::Begin("Terminal");
        // Input line
        if (ImGui::InputText("Command", inputBuffer, sizeof(inputBuffer),
                             ImGuiInputTextFlags_EnterReturnsTrue))
        {
            std::string cmd(inputBuffer);
            std::fill(std::begin(inputBuffer), std::end(inputBuffer), 0); // clear input

            ExecuteCommand(cmd);
            scrollToBottom = true;
        }

        if (ImGui::BeginChild("TerminalOutput", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true))
        {
            for (const auto& line : outputLines)
                ImGui::TextUnformatted(line.c_str());

            if (scrollToBottom)
            {
                ImGui::SetScrollHereY(1.0f);
                scrollToBottom = false;
            }
        }
        ImGui::EndChild();

        ImGui::End();
}
void Terminal::Update(float dt){};

void AssetPanel::Render(){
    ImGui::Begin(name.c_str());
    ImGui::Text("Total assets: %zu", Proj.Assets.m_Assets.size());
    
    float padding = 16.0f;
    float thumbnailSize = 96.0f;
    float cellSize = thumbnailSize + padding;

    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int)(panelWidth / cellSize);

    if (columnCount < 1)
        columnCount = 1;

    ImGui::Columns(columnCount, 0, false);

   for (auto& a : Proj.Assets.m_Assets){
    if (a->Type == AssetType::Material){
          
            auto mat = Proj.Assets.Get<MaterialAsset>(a->Handle);
            auto tex = mat ? mat->GetTexture().get() : nullptr;

            if (tex && tex->ID != 0){
 
                ImVec2 maxSize(128, 128); 
                float texWidth  = (float)tex->Width;  
                float texHeight = (float)tex->Height;

                float scale = std::min(maxSize.x / texWidth, maxSize.y / texHeight);

                ImVec2 previewSize(tex->Width * scale, texHeight * scale);
                ImGui::PushID(a->Handle);
 

                ImGui::Image((ImTextureID)(uintptr_t)tex->ID, previewSize, ImVec2(0,1), ImVec2(1,0));
                ImGui::TextWrapped("%u", a->Path.c_str()); // or file name
                if (ImGui::Button("Delete")) {
                    Proj.Assets.DeleteAsset(a->Handle);
                    Proj.Assets.DeleteAsset(tex->Handle);
                    ImGui::PopID();
                    break; // break to avoid iterator invalidation
                }

                ImGui::PopID();
            }
        ImGui::NextColumn();
     
        }
    }
    
    ImGui::Columns(1);
    ImGui::End();
}
void AssetPanel::Update(float dt){};

void EntityList::Render(){
    ImGui::Begin( name.c_str());
 
    scene* defaultScene = nullptr;

    for (auto& s : Proj.SceneList) {
        if (s.ID == SelectedScene) {
            defaultScene = &s;
            break;
        }
    }

    if (!defaultScene) {
        ImGui::Text("Please select a scene in SceneManager");
        ImGui::End();
        return;
    }

 
    if (defaultScene) {

        ImGui::Text(defaultScene->Scenename.c_str());
        ImGui::Separator();
    
        if (ImGui::Button("+", ImVec2(20, 20))) {
            Proj.AddEntity(defaultScene->ID);
        }
        
        ImGui::SameLine();
    
    
        if (ImGui::Button("X", ImVec2(20, 20))) {
            Proj.DeleteEntity(selection.EntityID);    
        }

        ImGui::Separator();

        if (defaultScene->EntityIDs.empty()) {
            ImGui::Text("No entities in this scene");
        } else {
            
            for (size_t i = 0; i < defaultScene->EntityIDs.size(); ++i) {

                uint32_t entityID = defaultScene->EntityIDs[i];
                entity* e = Proj.GetEntityByID(entityID);
 
                if (!e) continue;

      
                ImGui::PushID(entityID);

            
                bool selected = (selection.EntityID == e->ID);
                if (ImGui::Selectable(e->name.c_str(), selected)) {
    
                    selection.ClearEntity();
                
                    selection.EntityID = e->ID;
 
                }

                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                    ImGui::SetDragDropPayload("ENTITY_PAYLOAD", &i, sizeof(size_t));
                    ImGui::Text("Move %s", e->name.c_str());
                    ImGui::EndDragDropSource();
                }

  
                if (ImGui::BeginDragDropTarget()) {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_PAYLOAD")) {
                        ImGui::SameLine();

                        IM_ASSERT(payload->DataSize == sizeof(size_t));
                        size_t srcIndex = *(const size_t*)payload->Data;
 
                        if (srcIndex != i) {
                            auto& ids = defaultScene->EntityIDs;
                            uint32_t movedID = ids[srcIndex];
                            ids.erase(ids.begin() + srcIndex);
                            ids.insert(ids.begin() + i, movedID);
                        }
                    }
                    ImGui::EndDragDropTarget();
                }
                ImGui::PopID();
            }
        }
    }
     ImGui::End();
}

void EntityList::Update(float dt){};

void Inspector::Render(){

    entity* CurrentEntity = nullptr;
    uint32_t selectedID = selection.EntityID;

    for (auto& SelectedE : Proj.EntityList) {
        if (selection.EntityID == SelectedE.ID) {
            CurrentEntity = &SelectedE;
        }
    } 

    ImGui::Begin(name.c_str());
    
    if (!CurrentEntity) {
        ImGui::Text("No Entity Selected");
    }


    if (CurrentEntity != nullptr) {

        CurrentEntity->DrawInfoUI();

        auto& comps = CurrentEntity->ComponentIDs;

        uint32_t componentToDelete = 0;
        bool hasDeleteRequest = false;

        for (size_t i = 0; i < comps.size(); ++i) {    
            uint32_t compID = comps[i];
 
            if (Component* c = Proj.GetComponentByID(compID)) {
                ImGui::PushID(compID);
                ImGui::Dummy(ImVec2(1, 1));
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
                
                float totalButtonWidth = 60.0f; // 2 buttons × 20 width
                float spacing = 4.0f;
                float posX = ImGui::GetWindowContentRegionMax().x - totalButtonWidth - spacing;
                ImGui::SameLine(posX);

                bool requestDelete = false;

                if (ImGui::Button("X")) {
                    hasDeleteRequest = true;
                    componentToDelete = compID;
                        c->OnRemove(Proj.Assets);
                }

                ImGui::SameLine(0, 5.0f);

                if (ImGui::ArrowButton("##up", ImGuiDir_Up) && i > 0) {
                    std::swap(comps[i], comps[i - 1]);
                }

                ImGui::SameLine(0, 5.0f);

                if (ImGui::ArrowButton("##down", ImGuiDir_Down) && i + 1 < comps.size()) {
                    std::swap(comps[i], comps[i + 1]);
                }
                bool open = ImGui::CollapsingHeader(c->Getname().c_str(), flags);
 
                if (open) {
                    c->DrawComponentUI(Proj.Assets);
                }
           
                ImGui::PopID();
            }
        }

        if (hasDeleteRequest) {
            Proj.DeleteComponent(componentToDelete);
        }
        
        ImGui::Spacing(); 
        float width = ImGui::GetContentRegionAvail().x;
        if (ImGui::Button("Add Component", ImVec2(width, 0))) {

            ImGui::OpenPopup("ComponentSelectionPopup");
        }
        ImGui::SetNextWindowSizeConstraints(
            ImVec2(240, 0),     // minimum size
            ImVec2(360, FLT_MAX) // maximum size (very tall allowed)
            );

        ImGui::PushStyleColor(ImGuiCol_PopupBg,    ImVec4(0.12f, 0.13f, 0.17f, 0.98f));   // deep dark gray-blue
        ImGui::PushStyleColor(ImGuiCol_Border,     ImVec4(0.28f, 0.56f, 1.00f, 0.60f));   // soft but visible blue border 
        ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, 1.8f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 6.0f);                           // nice rounded corners 
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,   ImVec2(10.0f, 10.0f));          // comfortable inner spacing

        if (ImGui::BeginPopup("ComponentSelectionPopup")){

            uint32_t entityId = selection.EntityID;
            float avail_width = ImGui::GetContentRegionAvail().x;

            for (const auto& desc : ComponentRegistry::Get().All()){
                bool alreadyHas = desc.has(Proj, entityId);
                bool canAdd = desc.allowDupe || !alreadyHas;
                ImGui::BeginDisabled(!canAdd);
                if (ImGui::Button(desc.name.c_str(), ImVec2(avail_width, 0))){
                    if (canAdd){
                        desc.add(Proj, entityId);
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::EndDisabled();
                if (!canAdd && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)){
                    ImGui::SetTooltip("%s is already attached (duplicates not allowed)", desc.name.c_str());
                }
            }
     
            ImGui::EndPopup();
        }   
        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar(3);

    }
 
    ImGui::End();   
};
    
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

void Inspector::Update(float dt){};

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

        if (ImGui::Button("T")) {
            mode = ImGuizmo::TRANSLATE;
        }
     ImGui::SameLine();
        if (ImGui::Button("R")) {
            mode = ImGuizmo::ROTATE_Z;
        }  
        ImGui::SameLine();
        if (ImGui::Button("S")) {
            mode = ImGuizmo::SCALE;
        }

        ImGui::SameLine();
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImGui::SetCursorPosX(windowSize.x - 200); // 80px from left edge

        ImGui::Checkbox("Grid", &m_renderer->DrawGrid);

        ImGui::SameLine();
        ImGui::Checkbox("Axis", &m_renderer->DrawAxis);
    
        ImGui::SameLine();
        if (ImGui::ArrowButton("##play",ImGuiDir_Right)) {
            LaunchRuntimeWindow();
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

