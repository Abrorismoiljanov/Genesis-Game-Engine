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
    files = {
        "Editor/ShaderUtils.cpp"
    },
    depfiles = "ShaderUtils.o: Editor/ShaderUtils.cpp include/ShaderUtils.h\
",
    depfiles_format = "gcc"
}