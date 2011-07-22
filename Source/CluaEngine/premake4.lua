
project "CassiusCluaEngine"
    kind "SharedLib"
    language "C++"
    objdir(getobjdir())
    targetdir(getdistdir())
    files {
        "*.cpp",
    }
    targetprefix("")
    links { "Cassius" }
    if _OPTIONS["with-lua"] == "own" then
        links { "lua" }
        -- why isn't this picked up by linking to "lua", when cxx-plugin's is?
        includedirs { getdepsdir() .. "/lua/src/" }
    else
        buildoptions { "`pkg-config --cflags lua5.1`" }
        linkoptions { "`pkg-config --libs lua5.1`" }
    end


