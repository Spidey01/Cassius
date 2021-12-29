# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

add_library(Cassius
    Engine.cpp
    Manager.cpp
    NativeFunction.cpp
    SourceStream.cpp
    SourceString.cpp)

target_include_directories(Cassius PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

target_link_libraries(Cassius PRIVATE CxxPlugin)

install(TARGETS Cassius
    EXPORT CassiusTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
