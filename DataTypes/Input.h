#pragma once

#include "SDL2/SDL.h"

class Input {
public:
    void ProcessEvent(const SDL_Event& e);
    void Update();

    bool IsKeyDown(int key);
    bool IsKeyPressed(int key);
    bool IsKeyReleased(int key);

    bool IsMouseDown(int button);
    bool IsMousePressed(int button);

    int GetMouseX();
    int GetMouseY();

private:
    bool keys[SDL_NUM_SCANCODES] = {};
    bool prevKeys[SDL_NUM_SCANCODES] = {};

    bool mouseButtons[8] = {};
    bool prevMouseButtons[8] = {};

    int mouseX = 0;
    int mouseY = 0;
};
