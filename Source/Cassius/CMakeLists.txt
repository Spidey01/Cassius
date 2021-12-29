# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

add_library(Cassius
    $<TARGET_OBJECTS:CxxPlugin>
    Engine.cpp
    Manager.cpp
    NativeFunction.cpp
    SourceStream.cpp
    SourceString.cpp)

target_include_directories(Cassius PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Deps/cxx-plugin/include>)
if (UNIX)
    target_link_libraries(Cassius -ldl)
endif (UNIX)

target_include_directories(Cassius PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

install(TARGETS Cassius
    EXPORT CassiusTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
