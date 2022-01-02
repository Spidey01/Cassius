# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
include(GNUInstallDirs)

add_library(CxxPlugin OBJECT cxx-plugin/src/CxxPlugin.cxx)
target_include_directories(CxxPlugin PUBLIC cxx-plugin/include)
# Note: targets need -ldl when using this object library on unix.

set_property(TARGET CxxPlugin PROPERTY POSITION_INDEPENDENT_CODE ON)

set(stdheaders_outdir "${PROJECT_BINARY_DIR}/Include/Cassius")
configure_file(cxxversion_and_stdheaders/cxxversion.hpp ${stdheaders_outdir}/cxxversion.hpp @ONLY)
configure_file(cxxversion_and_stdheaders/stdheaders.hpp ${stdheaders_outdir}/stdheaders.hpp @ONLY)

install(FILES
    ${stdheaders_outdir}/cxxversion.hpp
    ${stdheaders_outdir}/stdheaders.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})