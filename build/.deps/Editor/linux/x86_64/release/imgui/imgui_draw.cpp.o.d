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
    depfiles = "imgui_draw.o: imgui/imgui_draw.cpp imgui/imgui.h imgui/imconfig.h  imgui/imgui_internal.h imgui/imstb_rectpack.h imgui/imstb_truetype.h\
",
    depfiles_format = "gcc",
    files = {
        "imgui/imgui_draw.cpp"
    }
}