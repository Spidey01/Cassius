
project "CassiusCluaEngine"
    kind "SharedLib"
    language "C++"
    objdir(getobjdir())
    targetdir(getdistdir())
    files {
        "*.cpp",
    }
    targetprefix("")
    links { "Cassius", "lua" }
    if _OPTIONS["with-lua"] == "own" then
        includedirs { "Deps/lua/src/" }
    end


