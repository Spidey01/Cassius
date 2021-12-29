# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

add_subdirectory(Cassius)

if (LUA_FOUND)
    add_subdirectory(CluaEngine)
endif (LUA_FOUND)

if (Python_FOUND)
    add_subdirectory(CpythonEngine)
endif (Python_FOUND)
