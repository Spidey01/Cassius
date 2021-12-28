# vim: set filetype=cmake tabstop=4 shiftwidth=4 expandtab foldmethod=marker :
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

function(add_cassius_test name)
    add_executable(${name} ${name}.cpp Common.cpp)
    target_link_libraries(${name} Cassius)
    add_test(${name}_test ${name})
endfunction(add_cassius_test)

