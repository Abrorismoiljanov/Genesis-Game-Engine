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
    depfiles = "stb_image.o: Editor/stb_image.cpp include/stb_image.h\
",
    depfiles_format = "gcc",
    files = {
        "Editor/stb_image.cpp"
    }
}