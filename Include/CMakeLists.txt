# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

install(FILES
    Cassius/Cassius.hpp
    Cassius/CluaEngine.hpp
    Cassius/CpythonEngine.hpp
    Cassius/Engine.hpp
    Cassius/Engine.tpp
    Cassius/Manager.hpp
    Cassius/NativeFunction.hpp
    Cassius/Plugin.hpp
    Cassius/Source.hpp
    Cassius/SourceFile.hpp
    Cassius/SourceStream.hpp
    Cassius/SourceString.hpp
    Cassius/Value.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
