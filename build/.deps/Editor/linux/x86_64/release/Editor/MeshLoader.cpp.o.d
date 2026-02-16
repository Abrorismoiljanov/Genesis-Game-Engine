{
    depfiles = "MeshLoader.o: Editor/MeshLoader.cpp include/MeshLoader.h  DataTypes/Assets/ModelAsset.h DataTypes/Assets/Asset.h  DataTypes/Assets/MaterialAsset.h\
",
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
            "-IDataTypesDef",
            "-DNDEBUG"
        }
    },
    files = {
        "Editor/MeshLoader.cpp"
    }
}