-- premake build script for Cassius

dofile "Premake4/lib.lua"
dofile "Premake4/opts.lua"

solution "Cassius"
    dofile "Premake4/config.lua"
    include "Deps"
    include "Source"
--    include "Tests"

