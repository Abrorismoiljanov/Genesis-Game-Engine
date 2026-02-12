#pragma once
#include "string"
#include "project.h"
#include "Renderer.h"
#include "SelectedEntity.h"

class Panel{
public:
    explicit Panel(std::string name) : name(std::move(name)) {};

    virtual void Update() {};
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



class TestPanel : public Panel {
public:
    TestPanel(const std::string& n): Panel(n) {}

    void Render() override;


private:
};

class EntityList : public Panel{
public:
    EntityList(const std::string& n, project& Proj, SelectedEntity& selection): Panel(n), Proj(Proj), selection(selection) {}
    void Render() override;

private:
    project& Proj;
    SelectedEntity& selection;
};

class Inspector : public Panel{
public:
    Inspector(const std::string& n, project& Proj, SelectedEntity& selection):  Panel(n), Proj(Proj), selection(selection) {}
    void DrawAddComponentMenu(entity* CurrentEntity, project& Proj);
    void Render() override;

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
    
    void Render() override;

private:
    project& Proj;
    SelectedEntity& selection;
    Renderer* m_renderer;
};

