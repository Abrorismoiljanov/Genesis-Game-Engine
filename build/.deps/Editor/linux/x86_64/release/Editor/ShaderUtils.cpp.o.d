{
    depfiles = "ShaderUtils.o: Editor/ShaderUtils.cpp include/ShaderUtils.h\
",
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
        "Editor/ShaderUtils.cpp"
    }
}