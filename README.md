# MyGameEditor

A lightweight C++ game engine editor built with SDL2, OpenGL, ImGui, and stb_image.  
Designed to manage **Scenes**, **Entities**, and **Components** with a flexible editor UI.

---

## Features
-**Entity Component System**
  - you can control the behavior of Entities via components it owns.
  - Every Component will be shown in Inspector and you can tweak with it there.
- **Scene Management**  
  - Multiple scenes support.
  - you can tweak Scene settings in Scene Parameter Panel.
- **ImGui-based Editor**  
  - I used ImGui for UI
  - Flexible UI thanks to imGui and everyone who have done work around it
---

## Screenshots
![Editor Overview](./docs/Screenshots/Screenshot_20260225_111013.png)
![Editor Overview](./docs/Screenshots/Screenshot_20260226_131328.png)
![Editor Overview](./docs/Screenshots/Screenshot_20260226_150413.png)

### Prerequisites

- C++17 compatible compiler  
- [SDL2](https://www.libsdl.org/)  
- [OpenGL](https://www.opengl.org/)  
- [ImGui](https://github.com/ocornut/imgui)  
- [Stb_image](https://github.com/nothings/stb)  
- [xmake](https://xmake.io/#/) (build system)

### Build

Clone the repository:

```bash
git clone git@github.com:username/MyGameEditor.git
cd GGE
