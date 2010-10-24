-- premake build script for Cassius

solution "Cassius"
    configurations { "Development", "Release", "Debug" }

    project "Cassius"
        kind "SharedLib"
        language "C++"
        objdir(path.join("Build", project().name))
        targetdir(path.join("Dist", configurations()[1]))
        files { 
            "Include/**.hpp", 
            "Source/**.cpp",
        }

