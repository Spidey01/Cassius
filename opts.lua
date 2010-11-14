-- extra command line options for premake4

-- custom premake4 command line option to enable/disable the lua
-- StaticLib project in Deps/premake4.lua.
newoption {
    trigger     = "with-lua",
    value       = "own",
    description = "Use own static lib build of lua",
    allowed     = {
        { "system", "Use systems Lua" },
        { "own",    "Use own static Lua" },
    },
}
if not _OPTIONS["with-lua"] then
    _OPTIONS["with-lua"] = "system"
end


