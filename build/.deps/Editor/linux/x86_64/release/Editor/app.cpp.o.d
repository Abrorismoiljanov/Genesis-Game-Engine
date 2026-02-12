{
    files = {
        "Editor/app.cpp"
    },
    depfiles = "app.o: Editor/app.cpp include/App.h DataTypes/project.h DataTypes/scene.h  DataTypes/entity.h DataTypes/components.h DataTypes/AssetManager.h  imgui/imgui.h imgui/imconfig.h DataTypes/Assets/MaterialAsset.h  include/EditorUI.h include/Panels.h include/Renderer.h  include/FrameBuffer.h include/SelectedEntity.h  Editor/../imgui/backends/imgui_impl_opengl3.h  Editor/../imgui/backends/imgui_impl_sdl2.h imgui/imgui_internal.h  DataTypes/transformcomponent.h\
",
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