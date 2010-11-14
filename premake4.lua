-- premake build script for Cassius

dofile "lib.lua"

solution "Cassius"
    configurations { "Development", "Release", "Debug" }

    configuration "Development"
        flags { "ExtraWarnings" }
    configuration "Release"
        flags { "OptimizeSpeed" }
        defines { "NDEBUG" }
    configuration "Debug"
        flags { "Symbols", }

    include "Deps"

    project "Cassius"
        kind "SharedLib"
        language "C++"
        objdir(getobjdir())
        targetdir(getdistdir())
        make_Engine_templates() -- creates .tpp file for Engine class
        files { 
            "Include/**.hpp", 
            "Source/**.cpp",
        }
        excludes {
            -- files specific to other projects
            "Include/CluaEngine.cpp",
            "Source/CluaEngine.cpp",
            "Include/CpythonEngine.cpp",
            "Source/CpythonEngine.cpp",
        }
        links { "CxxPlugin" }
        includedirs { "Deps/cxx-plugin/include" }

    project "CassiusCluaEngine"
        kind "SharedLib"
        language "C++"
        objdir(getobjdir())
        targetdir(getdistdir())
        files {
            "Include/CluaEngine.hpp",
            "Source/CluaEngine.cpp",
        }
        targetprefix("")
        links { "Cassius", "lua" }

    project "CassiusCpythonEngine"
        kind "SharedLib"
        language "C++"
        objdir(getobjdir())
        targetdir(getdistdir())
        files {
            "Include/CpythonEngine.hpp",
            "Source/CpythonEngine.cpp",
        }
        targetprefix("")
        links { "Cassius" }
        if os.get() == 'windows' then print("warning: building python support on Windows not premade yet!") end
        configuration "gmake"
            buildoptions "`python-config --cflags`"
            linkoptions "`python-config --libs`"

