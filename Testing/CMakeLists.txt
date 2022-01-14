# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

function(add_cassius_test name)
    add_executable(${name} ${name}.cpp Common.cpp)
    target_link_libraries(${name} Cassius)
    add_test(${name}_test ${name})

    #
    # Path to the plugin files:
    # - dlopen() uses LD_LIBRARY_PATH.
    # - LibraryOpen() uses PATH.
    #
    if (DEFINED ld_library_path)
        if (UNIX)
            list(APPEND env_for_tests LD_LIBRARY_PATH=${ld_library_path})
        endif (UNIX)

        if (WIN32)
            # Windows and CMake both like semicolons.
            string(REPLACE ";" "\\\\;" escaped_path "$ENV{PATH};${ld_library_path}")
            list(APPEND env_for_tests "PATH=${escaped_path}")
        endif (WIN32)
    endif (DEFINED ld_library_path)

    if (DEFINED env_for_tests)
        set_property(TEST ${name}_test PROPERTY ENVIRONMENT ${env_for_tests})
        # get_property(testenv TEST ${name}_test PROPERTY ENVIRONMENT)
        # message("testenv ${name}_test: ${testenv}")
    endif()
endfunction(add_cassius_test)

if (WIN32)
    list(APPEND ld_library_path ${PROJECT_BINARY_DIR}/Source/Cassius)
endif (WIN32)

add_cassius_test(Value_List)
add_cassius_test(Value_bool)
add_cassius_test(Value_char)
add_cassius_test(Value_int)
add_cassius_test(Value_operators)
add_cassius_test(Value_ptr)
add_cassius_test(Value_real)
add_cassius_test(Value_string)

add_cassius_test(Source_String)

if (LUA_FOUND)
    list(APPEND ld_library_path ${PROJECT_BINARY_DIR}/Source/CluaEngine)

    add_cassius_test(lua_eval)
    add_cassius_test(lua_NativeFunction)
    add_cassius_test(lua_ScriptFunction)
endif (LUA_FOUND)

if (Python_FOUND)
    list(APPEND ld_library_path ${PROJECT_BINARY_DIR}/Source/CpythonEngine)
    add_cassius_test(python_eval)
endif (Python_FOUND)
