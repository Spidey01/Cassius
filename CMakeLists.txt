# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0...3.22 FATAL_ERROR)

if (NOT DEFINED ENV{VCPKG_ROOT} AND EXISTS "${PROJECT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "${PROJECT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif ()

project(Cassius
    VERSION 2.0
    LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build libs as shared." ON)
option(BUILD_TESTING "Enable CTest support." ON)
option(BUILD_PACKAGE "Enable CPack support." ON)
option(BUILD_DOCS "Enable Doxygen support." ON)
option(BUILD_EXAMPLE "Build example program with the library." ON)
option(ENABLE_REDIST "Enable copying redist files if using vcpkg." ON)
option(ENABLE_LUA "Enable Lua support if found." ON)
# Disabling by default, because old/WIP that doesn't compile on Python3.
option(ENABLE_PYTHON "Enable Python support if found." OFF)

include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
include(CassiusGuessTriplet)

# Pick up ./vcpkg if no VCPKG_ROOT.
# Pick up the toolchain file magically if VCPKG_ROOT is set.
# Best way to handle windows: vcpkg install the deps and set %VCPKG_ROOT%, or export the deps for .\vcpkg.
# On Linux: just use the distro package manager, or vcpkg.
if (NOT DEFINED ENV{VCPKG_ROOT} AND IS_DIRECTORY ${PROJECT_SOURCE_DIR}/vcpkg)
    set(ENV{VCPKG_ROOT} ${PROJECT_SOURCE_DIR}/vcpkg)
endif()
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

add_subdirectory(Include)
add_subdirectory(Source)
if (BUILD_EXAMPLE)
    add_subdirectory(Example)
endif (BUILD_EXAMPLE)

if (BUILD_TESTING)
    enable_testing()
    add_subdirectory(Testing)
endif (BUILD_TESTING)

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
    set(CPACK_RESOURCE_FILE_README ${PROJECT_SOURCE_DIR}/README.md)

    # Define CPACK_BINARY_<GENNAME> to control the CPACK_GENERATOR fields you want to build with.
    # E.g. cmake -DCPACK_BINARY_ZIP=ON -DCPACK_BINARY_DEB=ON.

    include(CPack)
endif (BUILD_PACKAGE)

if (BUILD_DOCS)
    if("${CMAKE_VERSION}" VERSION_LESS "3.12") 
        message("cmake >= 3.9 required for doxygen_add_docs().")
        message("cmake >= 3.12 required for ALL argument to doxygen_add_docs().")
    else()
        find_package(Doxygen)
    endif()

    if (DOXYGEN_FOUND)
        set(DOXYGEN_PROJECT_BRIEF "C++ library designed to easily embed scripting languages in programs.")
        set(DOXYGEN_PROJECT_NAME "Cassius")
        set(DOXYGEN_EXTRACT_ALL YES)
        set(DOXYGEN_STRIP_FROM_INC_PATH ${PROJECT_SOURCE_DIR}/include)
        set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/README.md")
        set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)

        doxygen_add_docs(docs
            ${PROJECT_SOURCE_DIR}/CHANGELOG.md
            ${PROJECT_SOURCE_DIR}/Include/
            ${PROJECT_SOURCE_DIR}/LICENSE.txt
            ${PROJECT_SOURCE_DIR}/README.md
            ALL
            COMMENT "Generate documentation with Doxygen")

        install(DIRECTORY ${PROJECT_BINARY_DIR}/docs/html
                DESTINATION ${CMAKE_INSTALL_DOCDIR})
    endif (DOXYGEN_FOUND)
endif (BUILD_DOCS)

if (ENABLE_REDIST)
    if (DEFINED ENV{VCPKG_ROOT})
        if (VCPKG_MANIFEST_MODE)
            set(vcprefix "${PROJECT_BINARY_DIR}/vcpkg_installed/$ENV{VCPKG_TRIPLET}")
        else ()
            set(vcprefix "$ENV{VCPKG_ROOT}/installed/$ENV{VCPKG_TRIPLET}")
        endif ()
        foreach(vcdir bin debug include lib misc share tools)
            if (IS_DIRECTORY ${vcprefix}/${vcdir})
                # Kind of kludgy but effective. When building a package the
                # GNUInstallDir variables are updated accordingly but
                # CMAKE_INSTALL_PREFIX/CPACK_PACKAGING_PREFIX can lead to pain and
                # suffering.
                install(DIRECTORY "${vcprefix}/${vcdir}" DESTINATION ${CMAKE_INSTALL_BINDIR}/..)
            endif()
        endforeach(vcdir)
    endif()
endif (ENABLE_REDIST)
