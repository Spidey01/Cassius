-- this file must be dofile'd from the active solution.

-- put generated build files into Build/gmake; etc
location(path.join(path.join(solution().basedir, "Build"), _ACTION))

configurations { "Development", "Release", "Debug" }

includedirs { path.join(solution().basedir, "Include") }

if os.get() == 'windows' then defines { "_WIN32" } 
else
    -- needed for some platforms, e.g. bsd; and preferable to have
    -- under Linux and Solaris.
    includedirs { "/usr/local/include" }
    libdirs { "/usr/local/lib" }
end

configuration "Development"
    flags { "ExtraWarnings" }
configuration "Release"
    flags { "OptimizeSpeed" }
    defines { "NDEBUG" }
configuration "Debug"
    flags { "Symbols", }

