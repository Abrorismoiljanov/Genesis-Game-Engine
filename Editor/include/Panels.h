#pragma once
#include "string"
#include "project.h"
#include "Renderer.h"
#include "SelectedEntity.h"
#include "ImGuizmo.h"
#include "Runtime/include/Runtime.h"
#include "IconsFontAwesome6.h"
#include "CommandSystem.h"

class Panel{
public:
    explicit Panel(std::string name) : name(std::move(name)) {};

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    const char* GetName() const { return name.c_str(); }

    virtual ~Panel() = default;

    void SetVisible(bool v) { isVisible = v; }
    bool IsVisible() const { return isVisible; }

protected:
    std::string name;
private:
    bool isVisible = true;
};
struct ResolutionPreset {
    const char* label;
    int w;
    int h;
};

static ResolutionPreset presets[] = {
    { "800x600 (4:3)", 800, 600 },
    { "1280x720 (HD)", 1280, 720 },
    { "1920x1080 (Full HD)", 1920, 1080 },
    { "2560x1440 (2K)", 2560, 1440 },
    { "3840x2160 (4K)", 3840, 2160 },
    { "Custom", 0, 0 }
};

class ProjectSettingsPanel : public Panel {
public:
    ProjectSettingsPanel(const std::string& n, project& proj): Panel(n), Proj(proj) {}

    void Render() override;
    void Update(float dt) override;

private:
    project& Proj;
};

class SceneManagerPanel: public Panel {
public:
    SceneManagerPanel(const std::string& n, project& proj, int& SelectedS): Panel(n), Proj(proj), SelectedScene(SelectedS) {}

    void Render() override;
    void Update(float dt) override;

private:
    project& Proj;

    int& SelectedScene;
};


class Terminal : public Panel {
public:
    Terminal(const std::string& n, project& proj, Logger* logger, CommandSystem* commandSystem): 
        Panel(n), 
        Proj(proj),
        Log(logger),
        CmdSystem(commandSystem) {}

    void Render() override;
    void Update(float dt) override;
 
    ImGuiIO& io = ImGui::GetIO(); 
    
    float fontSize = 20.0f;

    ImFont* myFont = io.Fonts->AddFontFromFileTTF(
        "/home/abror/Project/GGE/assets/fonts/JetBrainsMono-2.304/fonts/ttf/JetBrainsMono-Medium.ttf",
        fontSize
    );


    Logger* Log = nullptr;
    CommandSystem* CmdSystem = nullptr;

private:
    project& Proj;
};

class EntityList : public Panel{
public:
    EntityList(const std::string& n, project& Proj, SelectedEntity& selection, int& SelectedS):
        Panel(n), Proj(Proj), selection(selection), SelectedScene(SelectedS) {}
    void Render() override;
    void Update(float dt) override;

private:
    project& Proj;
    SelectedEntity& selection;
    int& SelectedScene;
};
class SceneParamPanel : public Panel{
public:
    SceneParamPanel(const std::string& n, project& Proj, int& SelectedS):
        Panel(n), Proj(Proj), SelectedScene(SelectedS) {}
    void Render() override;
    void Update(float dt) override;

private:
    project& Proj;
    int& SelectedScene;
};

class Inspector : public Panel{
public:
    Inspector(const std::string& n, project& Proj, SelectedEntity& selection, Renderer* renderer):
        Panel(n), Proj(Proj), selection(selection), m_renderer(renderer) {}
    void DrawAddComponentMenu(entity* CurrentEntity, project& Proj);
    void Render() override;
    void Update(float dt) override;

private:
    project& Proj;
    SelectedEntity& selection;
    Renderer* m_renderer;
};

class Viewport: public Panel{
public:
    Viewport(const std::string& n, project& Proj, SelectedEntity& selection, Renderer* renderer, int& SelectedScene, CoreRuntime& runtime): 
        Panel(n),
        Proj(Proj),
        selection(selection),
        m_renderer(renderer),
        SelectedScene(SelectedScene),
        Runtime(runtime){}
    

    void Update(float dt) override;
    void Render() override;


    ImGuizmo::OPERATION mode = ImGuizmo::TRANSLATE;
private:
    bool m_CapturingMouse = false;
    ImVec2 m_LastMousePos = {0,0};
    float deltatime;
    project& Proj;
    SelectedEntity& selection;
    int& SelectedScene;
    CoreRuntime& Runtime;
    Renderer* m_renderer;
};

