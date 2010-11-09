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
