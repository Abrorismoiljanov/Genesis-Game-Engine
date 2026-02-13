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
    files = {
        "Editor/MeshLoader.cpp"
    },
    depfiles = "MeshLoader.o: Editor/MeshLoader.cpp include/MeshLoader.h  DataTypes/MeshComponent.h DataTypes/components.h imgui/imgui.h  imgui/imconfig.h include/ImGuiFileDialog.h  include/ImGuiFileDialogConfig.h DataTypes/Assets/MaterialAsset.h  DataTypes/transformcomponent.h DataTypes/project.h DataTypes/scene.h  DataTypes/entity.h DataTypes/AssetManager.h DataTypes/Assets/MeshAsset.h\
"
}