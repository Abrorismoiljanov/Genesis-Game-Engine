#include "Runtime.h"

CoreRuntime::CoreRuntime(){

}

void CoreRuntime::Run(){
    if (Project.valid) {
        window = SDL_CreateWindow(
            Project.Param.name.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            Project.Param.WindowWidth,
            Project.Param.WindowWidth,
            Project.Param.WindowParam);
    }
}
