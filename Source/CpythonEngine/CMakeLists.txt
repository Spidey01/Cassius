# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Not tested yet.
add_library(CassiusCpythonEngine MODULE CpythonEngine.cpp)
target_link_libraries(CassiusCpythonEngine PRIVATE Cassius Python::Python)
target_compile_definitions(CassiusCpythonEngine PRIVATE -DCassius_EXPORTS)
set_target_properties(CassiusCpythonEngine PROPERTIES PREFIX "")
install(TARGETS CassiusCpythonEngine 
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
