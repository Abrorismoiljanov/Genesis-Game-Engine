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
    depfiles = "Panels.o: Editor/Panels.cpp include/Panels.h DataTypes/project.h  DataTypes/scene.h DataTypes/entity.h DataTypes/components.h  include/SelectedEntity.h imgui/imgui.h imgui/imconfig.h  include/CompRegister.h\
",
    files = {
        "Editor/Panels.cpp"
    }
}