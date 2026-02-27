#pragma once
#include "string"
#include "project.h"
#include "Renderer.h"
#include "SelectedEntity.h"
#include "ImGuizmo.h"

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


class AssetPanel : public Panel {
public:
    AssetPanel(const std::string& n, project& proj): Panel(n), Proj(proj) {}

    void Render() override;
    void Update(float dt) override;

private:
    project& Proj;
};

class Terminal : public Panel {
public:
    Terminal(const std::string& n, project& proj): Panel(n), Proj(proj) {}

    void Render() override;
    void Update(float dt) override;

    std::vector<std::string> outputLines; // terminal output buffer
    char inputBuffer[256] = "";           // current input line
    bool scrollToBottom = false;          // auto-scroll flag

    // List of allowed commands (your “command list”)
    std::vector<std::string> commandList = {
        "run",
        "clear",
        "help"
    };

    void LaunchRuntimeWindow(std::vector<std::string> outputLines){
    std::string tempScene = "temp_scene.json";
    if (!Proj.SaveToFile(tempScene)) {
        std::cerr << "[Editor] Failed to save project to " << tempScene << std::endl;
        return;
    }
    std::string cmd = "./Runtime " + tempScene;  // Linux/macOS

    std::cout << "[Editor] Launching Runtime window..." << std::endl;
    outputLines.push_back("[Editor] Launching Runtime window...");

    // Launch asynchronously so Editor stays usable
    std::thread runtimeThread([cmd]() {
        int ret = std::system(cmd.c_str());
        if (ret != 0){
                std::cout << "Runtime Exited with code" << ret << '\n';
            }
    });
        runtimeThread.detach();
    }

    void ExecuteCommand(const std::string& cmd){
        if (cmd.empty()) return;

        // Echo command in terminal
        outputLines.push_back("> " + cmd);

        // Basic command handling
        if (cmd == "clear")
        {
            outputLines.clear();
        }
        else if (cmd == "help")
        {
            outputLines.push_back("Available commands:");
            for (auto& c : commandList)
                outputLines.push_back("  " + c);
        }
        else if (cmd == "run"){
            LaunchRuntimeWindow(outputLines);
        }
        else
        {
            outputLines.push_back("Unknown command: " + cmd);
        }
    }
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

class Inspector : public Panel{
public:
    Inspector(const std::string& n, project& Proj, SelectedEntity& selection):  Panel(n), Proj(Proj), selection(selection) {}
    void DrawAddComponentMenu(entity* CurrentEntity, project& Proj);
    void Render() override;
    void Update(float dt) override;

private:
    project& Proj;
    SelectedEntity& selection;
};

class Viewport: public Panel{
public:
    Viewport(const std::string& n, project& Proj, SelectedEntity& selection, Renderer* renderer, int& SelectedScene): 
        Panel(n),
        Proj(Proj),
        selection(selection),
        m_renderer(renderer),
        SelectedScene(SelectedScene){}
    
    void Update(float dt) override;
    void Render() override;

    void LaunchRuntimeWindow(){
        std::string tempScene = "temp_scene.json";
    if (!Proj.SaveToFile(tempScene)) {
        std::cerr << "[Editor] Failed to save project to " << tempScene << std::endl;
        return;
    }
    std::string cmd = "./Runtime " + tempScene;  // Linux/macOS

    std::cout << "[Editor] Launching Runtime window..." << std::endl;

    // Launch asynchronously so Editor stays usable
    std::thread runtimeThread([cmd]() {
        int ret = std::system(cmd.c_str());
        if (ret != 0){
                std::cout << "Runtime Exited with code" << ret << '\n';
            }
    });
        runtimeThread.detach();
    }


    ImGuizmo::OPERATION mode = ImGuizmo::TRANSLATE;
private:
    bool m_CapturingMouse = false;
    ImVec2 m_LastMousePos = {0,0};
    float deltatime;
    project& Proj;
    SelectedEntity& selection;
    int& SelectedScene;
    Renderer* m_renderer;
};

