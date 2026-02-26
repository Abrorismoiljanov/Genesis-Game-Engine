{
    files = {
        "Runtime/stb_image.cpp"
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
    },
    depfiles = "stb_image.o: Runtime/stb_image.cpp include/stb_image.h\
",
    depfiles_format = "gcc"
}