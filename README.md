# Genesis Game Engine

A lightweight C++ 2D game engine editor built with SDL2, OpenGL, ImGui, and Lua scripting.

---

## Screenshots

![Editor Overview](./docs/Screenshots/1.png)
![Editor Overview](./docs/Screenshots/2.png)
![Editor Overview](./docs/Screenshots/3.png)

---

## Features

- **Entity Component System** — control entity behavior through components, tweak them in the Inspector
- **Scene Management** — multiple scenes, configurable scene settings
- **ImGui-based Editor** — flexible editor UI with docking and theming
- **Lua Scripting** — attach scripts to entities via sol2
- **Asset Management** — textures, scripts, and materials with drag-and-drop file dialogs

## Tech Stack

- C++17
- SDL2 + OpenGL
- [ImGui](https://github.com/ocornut/imgui) (docking branch)
- [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)
- [sol2](https://github.com/ThePhD/sol2)
- [Lua](https://www.lua.org/)
- [stb_image](https://github.com/nothings/stb)

## Prerequisites

- C++17 compiler (GCC, Clang, MSVC)
- SDL2, OpenGL, GLEW (system packages)
- [cart](https://github.com/Abrorismoiljanov/cart) build tool

## Build

```bash
git clone https://github.com/Abrorismoiljanov/Genesis-Game-Engine
cd Genesis-Game-Engine
cart build
```

## License

MIT
