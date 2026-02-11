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
    depfiles_format = "gcc",
    depfiles = "app.o: Editor/app.cpp include/App.h DataTypes/project.h DataTypes/scene.h  DataTypes/entity.h DataTypes/components.h include/EditorUI.h  include/Panels.h include/SelectedEntity.h imgui/imgui.h imgui/imconfig.h  Editor/../imgui/backends/imgui_impl_opengl3.h  Editor/../imgui/backends/imgui_impl_sdl2.h imgui/imgui_internal.h  DataTypes/transformcomponent.h\
",
    files = {
        "Editor/app.cpp"
    }
}