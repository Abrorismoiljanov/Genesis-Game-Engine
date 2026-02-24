{
    files = {
        "Editor/Renderer.cpp"
    },
    depfiles = "Renderer.o: Editor/Renderer.cpp include/ShaderUtils.h  include/FrameBuffer.h include/Renderer.h DataTypes/project.h  DataTypes/scene.h DataTypes/entity.h DataTypes/components.h  DataTypes/SpriteComponent.h DataTypes/Assets/Asset.h  DataTypes/Assets/MaterialAsset.h DataTypes/Assets/TextureAsset.h  include/stb_image.h imgui/imgui.h imgui/imconfig.h  DataTypes/AssetManager.h include/ImGuiFileDialog.h  include/ImGuiFileDialogConfig.h DataTypes/transformcomponent.h  include/ViewportCamera.h\
",
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
    }
}