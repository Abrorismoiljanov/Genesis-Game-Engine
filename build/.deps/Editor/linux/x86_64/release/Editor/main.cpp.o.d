{
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
    },
    files = {
        "Editor/main.cpp"
    },
    depfiles = "main.o: Editor/main.cpp include/App.h DataTypes/project.h  DataTypes/scene.h DataTypes/entity.h DataTypes/components.h  DataTypes/AssetManager.h imgui/imgui.h imgui/imconfig.h  DataTypes/Assets/Asset.h include/EditorUI.h include/Panels.h  include/Renderer.h include/FrameBuffer.h include/ViewportCamera.h  include/SelectedEntity.h\
"
}