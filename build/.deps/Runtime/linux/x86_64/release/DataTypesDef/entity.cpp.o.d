{
    depfiles_format = "gcc",
    depfiles = "entity.o: DataTypesDef/entity.cpp DataTypes/entity.h imgui/imgui.h  imgui/imconfig.h\
",
    files = {
        "DataTypesDef/entity.cpp"
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