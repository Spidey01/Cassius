# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

add_library(Cassius
    $<TARGET_OBJECTS:CxxPlugin>
    Engine.cpp
    Manager.cpp
    NativeFunction.cpp
    Plugin.cpp
    SourceStream.cpp
    SourceString.cpp)

target_include_directories(Cassius PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Deps/cxx-plugin/include>)
if (UNIX)
    target_link_libraries(Cassius -ldl)
endif (UNIX)

target_include_directories(Cassius PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/Include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

install(TARGETS Cassius
    EXPORT CassiusTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

include(GenerateExportHeader)
set(cassius_export_file_name ${PROJECT_BINARY_DIR}/Include/Cassius/cassius_export.hpp)
generate_export_header(Cassius
    EXPORT_FILE_NAME ${cassius_export_file_name})
install(FILES
    ${cassius_export_file_name}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
