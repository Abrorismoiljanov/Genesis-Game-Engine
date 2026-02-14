{
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
    },
    depfiles_format = "gcc",
    depfiles = "MeshLoader.o: Editor/MeshLoader.cpp include/MeshLoader.h  DataTypes/Assets/MeshAsset.h DataTypes/Assets/Asset.h\
"
}