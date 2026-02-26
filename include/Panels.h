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
        "run_runtime",
        "clear",
        "help"
    };

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
        else if (cmd == "run_runtime")
        {
            // Run Runtime exe (make sure path is correct)
            int ret = std::system("./Runtime temp_scene.json");
            outputLines.push_back("Runtime exited with code " + std::to_string(ret));
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
    EntityList(const std::string& n, project& Proj, SelectedEntity& selection): Panel(n), Proj(Proj), selection(selection) {}
    void Render() override;
    void Update(float dt) override;

private:
    project& Proj;
    SelectedEntity& selection;
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
    Viewport(const std::string& n, project& Proj, SelectedEntity& selection, Renderer* renderer): 
        Panel(n),
        Proj(Proj),
        selection(selection),
        m_renderer(renderer) {}
    
    void Update(float dt) override;
    void Render() override;

    ImGuizmo::OPERATION mode = ImGuizmo::TRANSLATE;
private:
    bool m_CapturingMouse = false;
    ImVec2 m_LastMousePos = {0,0};
    float deltatime;
    project& Proj;
    SelectedEntity& selection;
    Renderer* m_renderer;
};

