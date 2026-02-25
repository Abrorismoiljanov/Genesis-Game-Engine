{
    depfiles = "ImGuizmo.o: imgui/ImGuizmo.cpp imgui/imgui.h imgui/imconfig.h  imgui/imgui_internal.h imgui/ImGuizmo.h\
",
    files = {
        "imgui/ImGuizmo.cpp"
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
    },
    depfiles_format = "gcc"
}