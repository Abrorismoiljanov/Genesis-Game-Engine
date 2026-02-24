{
    files = {
        "DataTypesDef/AssetManager.cpp"
    },
    depfiles = "AssetManager.o: DataTypesDef/AssetManager.cpp DataTypes/AssetManager.h  imgui/imgui.h imgui/imconfig.h DataTypes/Assets/Asset.h  DataTypes/components.h\
",
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
            "-IDataTypesDef",
            "-DNDEBUG"
        }
    },
    depfiles_format = "gcc"
}