{
    files = {
        "Editor/ViewportCamera.cpp"
    },
    depfiles = "ViewportCamera.o: Editor/ViewportCamera.cpp\
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
    }
}