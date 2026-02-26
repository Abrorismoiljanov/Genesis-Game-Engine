{
    files = {
        "Runtime/main.cpp"
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
            "-DNDEBUG"
        }
    },
    depfiles = "main.o: Runtime/main.cpp include/Runtime.h DataTypes/project.h  DataTypes/scene.h DataTypes/entity.h DataTypes/components.h  DataTypes/SpriteComponent.h DataTypes/Assets/Asset.h  DataTypes/Assets/MaterialAsset.h DataTypes/Assets/TextureAsset.h  include/stb_image.h imgui/imgui.h imgui/imconfig.h  DataTypes/AssetManager.h include/ImGuiFileDialog.h  include/ImGuiFileDialogConfig.h\
",
    depfiles_format = "gcc"
}