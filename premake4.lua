-- premake build script for Cassius

dofile "lib.lua"
dofile "opts.lua"

solution "Cassius"
    configurations { "Development", "Release", "Debug" }

    if os.get() == 'windows' then defines { "_WIN32" } end

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
            "Source/Engine.cpp",
            "Source/SourceStream.cpp",
            "Source/Manager.cpp",
            "Source/SourceString.cpp"
        }
        links { "CxxPlugin" }
        includedirs { "Deps/cxx-plugin/include" }

    project "CassiusCluaEngine"
        kind "SharedLib"
        language "C++"
        objdir(getobjdir())
        targetdir(getdistdir())
        files {
            "Source/CluaEngine.cpp",
        }
        targetprefix("")
        links { "Cassius", "lua" }
        if _OPTIONS["with-lua"] == "own" then
            includedirs { "Deps/lua/src/" }
        end

    project "CassiusCpythonEngine"
        kind "SharedLib"
        language "C++"
        objdir(getobjdir())
        targetdir(getdistdir())
        files {
            "Source/CpythonEngine.cpp",
        }
        targetprefix("")
        links { "Cassius" }
        if os.get() == 'windows' then
           print("warning: building python support on Windows not premade yet!")
        end
        configuration "gmake"
            buildoptions "`python-config --cflags`"
            linkoptions "`python-config --libs`"

