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
    files = {
        "Editor/Renderer.cpp"
    },
    depfiles_format = "gcc",
    depfiles = "Renderer.o: Editor/Renderer.cpp include/FrameBuffer.h include/Renderer.h  DataTypes/project.h DataTypes/scene.h DataTypes/entity.h  DataTypes/components.h DataTypes/AssetManager.h imgui/imgui.h  imgui/imconfig.h DataTypes/Assets/MaterialAsset.h\
"
}