# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(Cassius
    VERSION 2.0
    LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build libs as shared." ON)
option(BUILD_PACKAGE "Enable CPack support." ON)
option(ENABLE_LUA "Enable Lua support if found." ON)
option(ENABLE_PYTHON "Enable Python support if found." ON)

include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
include(CassiusGuessTriplet)

# Pick up the toolchain file magically if VCPKG_ROOT is set.
# Best way to handle windows: vcpkg install the deps and set %VCPKG_ROOT%.
# On Linux: just use the distro package manager, or vcpkg.
CassiusGuessTriplet(CassiusTriplet)
if(DEFINED ENV{VCPKG_ROOT})
    if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    endif()
    if(NOT DEFINED VCPKG_TRIPLET)
        # set(VCPKG_TRIPLET "${CassiusTriplet}" CACHE STRING "")
        set(ENV{VCPKG_TRIPLET} "${CassiusTriplet}")
    endif()
    list(APPEND CMAKE_PREFIX_PATH $ENV{VCPKG_ROOT}/installed/$ENV{VCPKG_TRIPLET})
    message(STATUS "VCPKG_ROOT: $ENV{VCPKG_ROOT} VCPKG_TRIPLET: ${VCPKG_TRIPLET} CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
endif()

add_subdirectory(Deps)

if (ENABLE_LUA)
    # Note: to use Lua 5.4, you'll need cmake >= 3.18.
    # To see more logging from FindLua.cmake set LUA_Debug to true
    find_package(Lua)
endif (ENABLE_LUA)

# Cassius 1.x never ported Python module off UNIX.
if (ENABLE_PYTHON AND NOT WIN32)
    # Note: requires cmake >= 3.12.
    find_package(Python COMPONENTS Development)
endif (ENABLE_PYTHON AND NOT WIN32)

add_library(Cassius
    Source/Cassius/Engine.cpp
    Source/Cassius/Manager.cpp
    Source/Cassius/NativeFunction.cpp
    Source/Cassius/SourceStream.cpp
    Source/Cassius/SourceString.cpp)

target_include_directories(Cassius PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

target_link_libraries(Cassius PRIVATE CxxPlugin)

if (LUA_FOUND)
    # FindLua.cmake doesn't make a target, just variables.
    add_library(CassiusCluaEngine MODULE Source/CluaEngine/CluaEngine.cpp Source/CluaEngine/funcs.cpp)
    target_link_libraries(CassiusCluaEngine PRIVATE Cassius ${LUA_LIBRARIES})
    target_include_directories(CassiusCluaEngine PRIVATE ${LUA_INCLUDE_DIR})
    set_target_properties(CassiusCluaEngine PROPERTIES PREFIX "")
    install(TARGETS CassiusCluaEngine
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif (LUA_FOUND)

if (Python_FOUND)
    # Not tested yet.
    add_library(CassiusPythonEngine MODULE Source/CPythonEngine/CPythonEngine.cpp)
    target_link_libraries(CassiusPythonEngine PRIVATE Cassius Python::Python)
    set_target_properties(CassiusPythonEngine PROPERTIES PREFIX "")
    install(TARGETS CassiusPythonEngine
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif (Python_FOUND)

install(TARGETS Cassius
    EXPORT CassiusTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
    Include/Cassius/Cassius.hpp
    Include/Cassius/CluaEngine.hpp
    Include/Cassius/CpythonEngine.hpp
    Include/Cassius/Engine.hpp
    Include/Cassius/Engine.tpp
    Include/Cassius/Manager.hpp
    Include/Cassius/NativeFunction.hpp
    Include/Cassius/Source.hpp
    Include/Cassius/SourceFile.hpp
    Include/Cassius/SourceStream.hpp
    Include/Cassius/SourceString.hpp
    Include/Cassius/Value.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

if (BUILD_PACKAGE)
    include(CMakePackageConfigHelpers)

    configure_package_config_file(${PROJECT_NAME}Config.cmake.in
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

    install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

    write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY SameMajorVersion)
    install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

    install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake/${PROJECT_NAME})

    set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
    set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/LICENSE.txt)
    set(CPACK_RESOURCE_FILE_README ${PROJECT_SOURCE_DIR}/README)

    # Define CPACK_BINARY_<GENNAME> to control the CPACK_GENERATOR fields you want to build with.
    # E.g. cmake -DCPACK_BINARY_ZIP=ON -DCPACK_BINARY_DEB=ON.

    include(CPack)
endif (BUILD_PACKAGE)
