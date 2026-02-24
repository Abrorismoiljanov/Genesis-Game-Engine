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
    depfiles = "Panels.o: Editor/Panels.cpp include/Panels.h DataTypes/project.h  DataTypes/scene.h DataTypes/entity.h DataTypes/components.h  DataTypes/SpriteComponent.h DataTypes/Assets/Asset.h  DataTypes/Assets/MaterialAsset.h DataTypes/Assets/TextureAsset.h  include/stb_image.h imgui/imgui.h imgui/imconfig.h  DataTypes/AssetManager.h include/ImGuiFileDialog.h  include/ImGuiFileDialogConfig.h DataTypes/transformcomponent.h  include/Renderer.h include/FrameBuffer.h include/ViewportCamera.h  include/SelectedEntity.h include/CompRegister.h\
",
    files = {
        "Editor/Panels.cpp"
    },
    depfiles_format = "gcc"
}