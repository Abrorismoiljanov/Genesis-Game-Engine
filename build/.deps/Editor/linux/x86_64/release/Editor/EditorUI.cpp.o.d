{
    files = {
        "Editor/EditorUI.cpp"
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
    depfiles = "EditorUI.o: Editor/EditorUI.cpp include/EditorUI.h include/Panels.h  DataTypes/project.h DataTypes/scene.h DataTypes/entity.h  DataTypes/components.h DataTypes/AssetManager.h imgui/imgui.h  imgui/imconfig.h DataTypes/Assets/MaterialAsset.h include/Renderer.h  include/FrameBuffer.h include/SelectedEntity.h  Editor/../imgui/backends/imgui_impl_opengl3.h  Editor/../imgui/backends/imgui_impl_sdl2.h  include/ComponentRegisterList.h include/CompRegister.h  DataTypes/transformcomponent.h DataTypes/MeshComponent.h  include/ImGuiFileDialog.h include/ImGuiFileDialogConfig.h  DataTypes/Assets/MeshAsset.h\
"
}