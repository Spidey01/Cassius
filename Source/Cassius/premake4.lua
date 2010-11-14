
project "Cassius"
    kind "SharedLib"
    language "C++"
    objdir(getobjdir())
    targetdir(getdistdir())
    make_Engine_templates() -- creates .tpp file for Engine class
    files { 
        "*.cpp",
    }
    links { "CxxPlugin" }
    includedirs { path.join(getdepsdir(), "cxx-plugin/include") }

