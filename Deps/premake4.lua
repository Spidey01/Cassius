-- premake4 build script for dependencies of Cassius

-- used for loading backends
--
project "CxxPlugin"
language "C++"
kind "StaticLib"
targetdir(os.getcwd())  -- this will be in THIS directory
files {
    "cxx-plugin/include/*.*",
    "cxx-plugin/src/**.cxx"
}
includedirs { "cxx-plugin/include" }

project "lua"
language "C"
kind "StaticLib"
targetdir(os.getcwd())
files {
    "lua/src/lapi.c", "lua/src/lcode.c", "lua/src/ldebug.c", "lua/src/ldo.c",
    "lua/src/ldump.c", "lua/src/lfunc.c", "lua/src/lgc.c", "lua/src/llex.c",
    "lua/src/lmem.c", "lua/src/lobject.c", "lua/src/lopcodes.c",
    "lua/src/lparser.c", "lua/src/lstate.c", "lua/src/lstring.c",
    "lua/src/ltable.c", "lua/src/ltm.c", "lua/src/lundump.c", "lua/src/lvm.c",
    "lua/src/lzio.c", "lua/src/lauxlib.c", "lua/src/lbaselib.c",
    "lua/src/ldblib.c", "lua/src/liolib.c", "lua/src/lmathlib.c",
    "lua/src/loslib.c", "lua/src/ltablib.c", "lua/src/lstrlib.c",
    "lua/src/loadlib.c", "lua/src/linit.c"
}
includedirs { "lua/src" }
