# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0...3.22 FATAL_ERROR)

project(CassiusExample
    VERSION 1.0
    LANGUAGES CXX)

if (NOT BUILD_EXAMPLE)
    # Standalone build using a Cassius package, install, etc.
    find_package(Cassius REQUIRED)
    add_library(Cassius ALIAS Cassius::Cassius)
endif (NOT BUILD_EXAMPLE)

add_executable(cassius_repl
    Interp.cpp
    main.cpp)
target_link_libraries(cassius_repl Cassius)

if (BUILD_PACKAGE)
    install(TARGETS cassius_repl RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif (BUILD_PACKAGE)