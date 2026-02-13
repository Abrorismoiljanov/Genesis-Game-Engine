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
    depfiles = "ImGuiFileDialog.o: ImGuiFileDialog/ImGuiFileDialog.cpp  ImGuiFileDialog/ImGuiFileDialog.h  ImGuiFileDialog/ImGuiFileDialogConfig.h imgui/imgui.h imgui/imconfig.h  imgui/imgui_internal.h\
",
    depfiles_format = "gcc",
    files = {
        "ImGuiFileDialog/ImGuiFileDialog.cpp"
    }
}