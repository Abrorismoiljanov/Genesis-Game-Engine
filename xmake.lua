set_project("GGE")
set_version("0.1.0")

add_rules("mode.debug", "mode.release")

-- xmake will auto-fetch these packages
add_requires("imgui v1.92.7-docking", {configs = {sdl2_no_renderer = true, opengl3 = true}})
add_requires("imguizmo", "sdl2", "glm", "nlohmann_json")
set_policy("package.sync_requires_to_deps", true)
add_requireconfs("imguizmo.imgui", {override = true, version = "v1.92.7-docking", configs = {sdl2_no_renderer = true, opengl3 = true}})

target("Editor")
    set_kind("binary")
    set_languages("cxx17")
    set_rundir(".")

    add_packages("imgui", "imguizmo", "sdl2", "glm", "nlohmann_json")

    add_defines("SOL_NO_LUA_HPP=1", "IMGUI_IMPL_OPENGL_LOADER_CUSTOM")
    add_cxflags("-include GL/glew.h")

    if is_plat("linux") then
        add_links("GLEW")
        add_syslinks("GL", "pthread", "dl")
    elseif is_plat("macosx") then
        add_syslinks("pthread")
        add_frameworks("OpenGL", "Cocoa", "IOKit", "CoreVideo")
    elseif is_plat("windows") then
        add_syslinks("opengl32", "gdi32")
    end

    add_includedirs(
        ".",
        "DataTypes",
        "DataTypesDef",
        "sol",
        "vendor/lua",
        "Editor/include",
        "Runtime/include",
        "ImGuiFileDialog"
    )

    add_files(
        "Editor/src/*.cpp",
        "Runtime/src/*.cpp",
        "DataTypesDef/*.cpp",
        "vendor/lua/lapi.c",
        "vendor/lua/lauxlib.c",
        "vendor/lua/lbaselib.c",
        "vendor/lua/lcode.c",
        "vendor/lua/lcorolib.c",
        "vendor/lua/lctype.c",
        "vendor/lua/ldblib.c",
        "vendor/lua/ldebug.c",
        "vendor/lua/ldo.c",
        "vendor/lua/ldump.c",
        "vendor/lua/lfunc.c",
        "vendor/lua/lgc.c",
        "vendor/lua/linit.c",
        "vendor/lua/liolib.c",
        "vendor/lua/llex.c",
        "vendor/lua/lmathlib.c",
        "vendor/lua/lmem.c",
        "vendor/lua/loadlib.c",
        "vendor/lua/lobject.c",
        "vendor/lua/lopcodes.c",
        "vendor/lua/loslib.c",
        "vendor/lua/lparser.c",
        "vendor/lua/lstate.c",
        "vendor/lua/lstring.c",
        "vendor/lua/lstrlib.c",
        "vendor/lua/ltable.c",
        "vendor/lua/ltablib.c",
        "vendor/lua/ltm.c",
        "vendor/lua/lundump.c",
        "vendor/lua/lutf8lib.c",
        "vendor/lua/lvm.c",
        "vendor/lua/lzio.c",
        "ImGuiFileDialog/ImGuiFileDialog.cpp"
    )


--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

