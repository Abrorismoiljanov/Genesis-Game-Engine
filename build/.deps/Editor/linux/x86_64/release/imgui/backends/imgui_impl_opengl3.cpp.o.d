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
    depfiles = "imgui_impl_opengl3.o: imgui/backends/imgui_impl_opengl3.cpp imgui/imgui.h  imgui/imconfig.h imgui/backends/imgui_impl_opengl3.h  imgui/backends/imgui_impl_opengl3_loader.h\
",
    depfiles_format = "gcc",
    files = {
        "imgui/backends/imgui_impl_opengl3.cpp"
    }
}