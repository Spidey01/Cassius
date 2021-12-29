# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# FindLua.cmake doesn't make a target, just variables.
add_library(CassiusCluaEngine MODULE CluaEngine.cpp funcs.cpp)
target_link_libraries(CassiusCluaEngine PRIVATE Cassius ${LUA_LIBRARIES})
target_include_directories(CassiusCluaEngine PRIVATE ${LUA_INCLUDE_DIR})
set_target_properties(CassiusCluaEngine PROPERTIES PREFIX "")
install(TARGETS CassiusCluaEngine
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})