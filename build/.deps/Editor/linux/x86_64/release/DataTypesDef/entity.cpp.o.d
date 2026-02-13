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
    depfiles = "entity.o: DataTypesDef/entity.cpp DataTypes/entity.h imgui/imgui.h  imgui/imconfig.h\
",
    depfiles_format = "gcc",
    files = {
        "DataTypesDef/entity.cpp"
    }
}