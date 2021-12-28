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
endif (LUA_FOUND)

if (Python_FOUND)
    add_cassius_test(python_eval)
endif (Python_FOUND)
