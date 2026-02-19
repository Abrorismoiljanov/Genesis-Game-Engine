{
    depfiles_format = "gcc",
    depfiles = "Renderer.o: Editor/Renderer.cpp include/ShaderUtils.h  include/FrameBuffer.h include/Renderer.h DataTypes/project.h  DataTypes/scene.h DataTypes/entity.h DataTypes/components.h  DataTypes/AssetManager.h imgui/imgui.h imgui/imconfig.h  DataTypes/Assets/Asset.h include/ViewportCamera.h  DataTypes/transformcomponent.h DataTypes/SpriteComponent.h  DataTypes/Assets/MaterialAsset.h DataTypes/Assets/TextureAsset.h  include/stb_image.h include/ImGuiFileDialog.h  include/ImGuiFileDialogConfig.h\
",
    files = {
        "Editor/Renderer.cpp"
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