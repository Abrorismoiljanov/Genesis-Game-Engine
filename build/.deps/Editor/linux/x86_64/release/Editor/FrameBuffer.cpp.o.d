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
    depfiles = "FrameBuffer.o: Editor/FrameBuffer.cpp include/FrameBuffer.h\
",
    depfiles_format = "gcc",
    files = {
        "Editor/FrameBuffer.cpp"
    }
}