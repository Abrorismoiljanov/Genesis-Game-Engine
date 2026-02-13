#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "SDL2/SDL.h"


class ViewportCamera {
public:
    void SetViewportSize(int w, int h) {
        ViewWidth = w;
        ViewHeight = h;
    }

    void ProcessMouseMotion(float dx, float dy) {
        yaw   += dx * MouseSpeed;
        pitch -= dy * MouseSpeed;

        if (pitch > 89.0f)  pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        UpdateVectors();
    }

    void ProcessKeyboard(const Uint8* keystate, float dt) {
        float velocity = MoveSpeed * dt;
        if (keystate[SDL_SCANCODE_W]) Position += Front * velocity;
        if (keystate[SDL_SCANCODE_S]) Position -= Front * velocity;
        if (keystate[SDL_SCANCODE_A]) Position -= Right * velocity;
        if (keystate[SDL_SCANCODE_D]) Position += Right * velocity;
    }

    glm::mat4 GetView() const {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::mat4 GetProjection() const {
        return glm::perspective(glm::radians(FOV), (float)ViewWidth / ViewHeight, Near, Far);
    }

private:
    void UpdateVectors() {
        // Recalculate front vector from yaw/pitch
        glm::vec3 front;
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Front));
    }

private:
    glm::vec3 Position {0,0,5};
    glm::vec3 Front {0,0,-1};
    glm::vec3 Up {0,1,0};
    glm::vec3 Right {1,0,0};
    const glm::vec3 WorldUp {0,1,0};

    float yaw   = -90.0f; // init looking down -Z
    float pitch = 0.0f;
    float FOV = 60.0f;
    float Near = 0.1f, Far = 100.0f;
    float MoveSpeed = 5.0f;
    float MouseSpeed = 0.1f;

    int ViewWidth = 1920;
    int ViewHeight = 1080;
};
