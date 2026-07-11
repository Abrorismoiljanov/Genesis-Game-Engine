#include "Editor/include/App.h"
#include "DataTypes/outside/FilePaths.h"

int main(int argc, char **argv) {

    FilePaths::SetProjectRootFromCwd();

    app App;
    App.Init();
    App.Run();

    return 0;
}
