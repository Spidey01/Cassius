-- premake build script for Cassius

solution "Cassius"
    configurations { "Development", "Release", "Debug" }

    project "Cassius"
        kind "SharedLib"
        language "C++"
        files { 
            "Include/**.hpp", 
            "Source/**.cpp",
        }

