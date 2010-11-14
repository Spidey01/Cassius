
project "CassiusCpythonEngine"
    kind "SharedLib"
    language "C++"
    objdir(getobjdir())
    targetdir(getdistdir())
    files {
        "*.cpp",
    }
    targetprefix("")
    links { "Cassius" }
    configuration "gmake"
        buildoptions "`python-config --cflags`"
        linkoptions "`python-config --libs`"
