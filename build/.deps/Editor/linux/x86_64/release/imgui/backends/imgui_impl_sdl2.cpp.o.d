{
    depfiles = "imgui_impl_sdl2.o: imgui/backends/imgui_impl_sdl2.cpp imgui/imgui.h  imgui/imconfig.h imgui/backends/imgui_impl_sdl2.h\
",
    depfiles_format = "gcc",
    files = {
        "imgui/backends/imgui_impl_sdl2.cpp"
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