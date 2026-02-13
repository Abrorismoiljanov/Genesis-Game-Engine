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
    depfiles = "imgui_widgets.o: imgui/imgui_widgets.cpp imgui/imgui.h imgui/imconfig.h  imgui/imgui_internal.h imgui/imstb_textedit.h\
",
    depfiles_format = "gcc",
    files = {
        "imgui/imgui_widgets.cpp"
    }
}