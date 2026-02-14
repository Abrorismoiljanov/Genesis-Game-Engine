{
    files = {
        "DataTypesDef/AssetManager.cpp"
    },
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
    depfiles = "AssetManager.o: DataTypesDef/AssetManager.cpp DataTypes/AssetManager.h  imgui/imgui.h imgui/imconfig.h DataTypes/Assets/Asset.h  DataTypes/components.h DataTypes/MeshComponent.h  include/ImGuiFileDialog.h include/ImGuiFileDialogConfig.h  DataTypes/transformcomponent.h DataTypes/project.h DataTypes/scene.h  DataTypes/entity.h DataTypes/Assets/MeshAsset.h include/MeshLoader.h\
"
}