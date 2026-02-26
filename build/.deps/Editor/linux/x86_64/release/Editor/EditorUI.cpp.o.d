{
    depfiles = "EditorUI.o: Editor/EditorUI.cpp include/EditorUI.h include/Panels.h  DataTypes/project.h DataTypes/scene.h DataTypes/entity.h  DataTypes/components.h DataTypes/SpriteComponent.h  DataTypes/Assets/Asset.h DataTypes/Assets/MaterialAsset.h  DataTypes/Assets/TextureAsset.h include/stb_image.h imgui/imgui.h  imgui/imconfig.h DataTypes/AssetManager.h include/ImGuiFileDialog.h  include/ImGuiFileDialogConfig.h include/Renderer.h include/FrameBuffer.h  include/ViewportCamera.h include/SelectedEntity.h imgui/ImGuizmo.h  Editor/../imgui/backends/imgui_impl_opengl3.h  Editor/../imgui/backends/imgui_impl_sdl2.h  include/ComponentRegisterList.h include/CompRegister.h  DataTypes/transformcomponent.h\
",
    depfiles_format = "gcc",
    files = {
        "Editor/EditorUI.cpp"
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