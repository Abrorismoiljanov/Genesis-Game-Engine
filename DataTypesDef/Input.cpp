#include "DataTypes/Input.h"

void Input::ProcessEvent(const SDL_Event& e) {
    switch (e.type) {
        case SDL_KEYDOWN:
            keys[e.key.keysym.scancode] = true;
            break;

        case SDL_KEYUP:
            keys[e.key.keysym.scancode] = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseButtons[e.button.button] = true;
            break;

        case SDL_MOUSEBUTTONUP:
            mouseButtons[e.button.button] = false;
            break;

        case SDL_MOUSEMOTION:
            mouseX = e.motion.x;
            mouseY = e.motion.y;
            break;
    }
}
void Input::Update() {
    memcpy(prevKeys, keys, sizeof(keys));
    memcpy(prevMouseButtons, mouseButtons, sizeof(mouseButtons));
}
bool Input::IsKeyDown(int key) {
    if (key < 0 || key >= SDL_NUM_SCANCODES) return false;
    return keys[key];
}

bool Input::IsKeyPressed(int key) {
    if (key < 0 || key >= SDL_NUM_SCANCODES) return false;
    return keys[key] && !prevKeys[key];
}

bool Input::IsKeyReleased(int key) {
    if (key < 0 || key >= SDL_NUM_SCANCODES) return false;
    return !keys[key] && prevKeys[key];
}
