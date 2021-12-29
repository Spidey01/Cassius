# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Not tested yet.
add_library(CassiusPythonEngine MODULE CPythonEngine.cpp)
target_link_libraries(CassiusPythonEngine PRIVATE Cassius Python::Python)
set_target_properties(CassiusPythonEngine PROPERTIES PREFIX "")
install(TARGETS CassiusPythonEngine
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})