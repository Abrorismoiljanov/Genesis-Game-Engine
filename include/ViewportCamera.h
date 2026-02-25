#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "SDL2/SDL.h"


class ViewportCamera {
public:
    void SetViewportSize(int w, int h) {
        ViewWidth = w;
        ViewHeight = h;
    }


    glm::mat4 GetViewMatrix() const{
        return glm::translate(
            glm::mat4(1.0f),
            glm::vec3(-Position, 0.0f)
        );
    }

    glm::mat4 GetProjectionMatrix() const{
        return glm::ortho(
            0.0f,
            (float)ViewWidth / Zoom,
            (float)ViewHeight / Zoom,
            0.0f,
            -1.0f,
            1.0f);
    }

    void Update(float dt, const Uint8* keys) {
        float velocity = MoveSpeed * dt;

        if (keys[SDL_SCANCODE_W]) Position.y += velocity;
        if (keys[SDL_SCANCODE_S]) Position.y -= velocity;
        if (keys[SDL_SCANCODE_A]) Position.x -= velocity;
        if (keys[SDL_SCANCODE_D]) Position.x += velocity;
    }

    void ProcessMousePan(float dx, float dy) {
        Position.x -= dx / Zoom;
        Position.y -= dy / Zoom;
    }


    void ProcessScroll(float scrollDelta, glm::vec2 mouseScreen){

        glm::vec2 before = ScreenToWorld(mouseScreen);
        Zoom += scrollDelta * 0.1f;
        Zoom = std::max(Zoom, 0.1f);
        glm::vec2 after = ScreenToWorld(mouseScreen);
        Position += before - after;
    }

    glm::vec2 ScreenToWorld(glm::vec2 screen) const{
        float worldX = screen.x / Zoom + Position.x;
        float worldY = screen.y / Zoom + Position.y;
        return { worldX, worldY };
    }

    glm::mat4 GetViewProjection() const {
        return GetProjectionMatrix() * GetViewMatrix();
    }


    float Zoom = 0.8f;
    glm::vec2 Position{-1.0f, -1.0f};
    int ViewWidth = 1280;
    int ViewHeight = 1080;
    int HalfWidth = ViewWidth/2;
    int HalfHeight = ViewHeight/2;
    float MoveSpeed = 500.0f;
};
