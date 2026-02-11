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
    depfiles = "main.o: Editor/main.cpp include/App.h DataTypes/project.h  DataTypes/scene.h DataTypes/entity.h DataTypes/components.h  include/EditorUI.h include/Panels.h include/SelectedEntity.h\
",
    files = {
        "Editor/main.cpp"
    }
}