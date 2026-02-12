{
    files = {
        "Editor/Panels.cpp"
    },
    depfiles = "Panels.o: Editor/Panels.cpp include/Panels.h DataTypes/project.h  DataTypes/scene.h DataTypes/entity.h DataTypes/components.h  DataTypes/AssetManager.h imgui/imgui.h imgui/imconfig.h  DataTypes/Assets/MaterialAsset.h include/Renderer.h  include/FrameBuffer.h include/SelectedEntity.h include/CompRegister.h\
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