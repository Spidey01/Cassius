# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
include(GNUInstallDirs)

add_library(CxxPlugin OBJECT cxx-plugin/src/CxxPlugin.cxx)
target_include_directories(CxxPlugin PUBLIC cxx-plugin/include)
if (UNIX)
    target_link_libraries(CxxPlugin -ldl)
endif()
