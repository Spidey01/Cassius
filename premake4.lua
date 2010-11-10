-- premake build script for Cassius

function getobjdir()
    return path.join("Build", project().name)
end
function getdistdir()
    return path.join("Dist", configurations()[1])
end

solution "Cassius"
    configurations { "Development", "Release", "Debug" }

    include "Deps"

    project "Cassius"
        kind "SharedLib"
        language "C++"
        objdir(getobjdir())
        targetdir(getdistdir())
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
        links "lua"

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
        if os.get() == 'windows' then print("warning: building python support on Windows not premade yet!") end
        configuration "gmake"
            buildoptions "`python-config --cflags`"
            linkoptions "`python-config --libs`"

