{
    files = {
        "Runtime/main.cpp"
    },
    depfiles_format = "gcc",
    values = {
        "/usr/bin/g++",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-Iinclude",
            "-IDataTypes",
            "-Iimgui",
            "-Iimgui/backends",
            "-DNDEBUG"
        }
    },
    depfiles = "main.o: Runtime/main.cpp include/Runtime.h DataTypes/project.h  DataTypes/scene.h DataTypes/entity.h DataTypes/components.h  DataTypes/AssetManager.h imgui/imgui.h imgui/imconfig.h  DataTypes/Assets/Asset.h\
"
}