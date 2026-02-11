{
    depfiles = "imgui.o: imgui/imgui.cpp imgui/imgui.h imgui/imconfig.h  imgui/imgui_internal.h\
",
    depfiles_format = "gcc",
    files = {
        "imgui/imgui.cpp"
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
            "-IDataTypesDef",
            "-DNDEBUG"
        }
    }
}