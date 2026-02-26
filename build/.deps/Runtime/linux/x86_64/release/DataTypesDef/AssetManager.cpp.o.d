{
    depfiles_format = "gcc",
    depfiles = "AssetManager.o: DataTypesDef/AssetManager.cpp DataTypes/AssetManager.h  imgui/imgui.h imgui/imconfig.h DataTypes/Assets/Asset.h  DataTypes/components.h\
",
    files = {
        "DataTypesDef/AssetManager.cpp"
    },
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
    }
}