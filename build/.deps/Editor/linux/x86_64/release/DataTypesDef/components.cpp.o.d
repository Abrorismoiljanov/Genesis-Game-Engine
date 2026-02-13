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
    depfiles = "components.o: DataTypesDef/components.cpp DataTypes/components.h\
",
    depfiles_format = "gcc",
    files = {
        "DataTypesDef/components.cpp"
    }
}