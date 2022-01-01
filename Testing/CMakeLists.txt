# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

function(add_cassius_test name)
    add_executable(${name} ${name}.cpp Common.cpp)
    target_link_libraries(${name} Cassius)
    add_test(${name}_test ${name})
endfunction(add_cassius_test)

add_cassius_test(Value_bool)
add_cassius_test(Value_char)
add_cassius_test(Value_int)
add_cassius_test(Value_ptr)
add_cassius_test(Value_real)
add_cassius_test(Value_string)
add_cassius_test(Value_List)

add_cassius_test(Source_String)

if (LUA_FOUND)
    add_cassius_test(lua_eval)

    # lua.dll needs to be next to the exe or the plugin. LoadLibrary() considers
    # PATH to find the plugin itself, but () will attempt to load
    # CassiusCluaEngine.dll and then fail because lua.dll was not found even
    # though it is in PATH.

    if (WIN32 AND DEFINED ENV{VCPKG_ROOT})
        configure_file("$ENV{VCPKG_ROOT}/installed/$ENV{VCPKG_TRIPLET}/bin/lua.dll" ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
    endif (WIN32 AND DEFINED ENV{VCPKG_ROOT})
endif (LUA_FOUND)

if (Python_FOUND)
    add_cassius_test(python_eval)
endif (Python_FOUND)
