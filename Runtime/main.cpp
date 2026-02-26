#include "Runtime.h"

int main (int argc, char *argv[]) {
    std::string projectFile = (argc >= 2) ? argv[1] : "";
    CoreRuntime Runtime;
    Runtime.Init(projectFile);
    Runtime.Run();
    return 0;

}
