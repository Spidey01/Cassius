#ifndef CASSIUS_TESTING_COMMON_HPP
#define CASSIUS_TESTING_COMMON_HPP
// SPDX-License-Identifier: ISC
/* Copyright 2021, the Cassius authors. */

/*
 * Include this in each test program and link using Common.cpp to provide the main().
 */

/** Called from main() in Common.cpp.
 * 
 * Define a function like this and linking to Common.cpp provides the main() to call it.
 * 
 * @param name the test program name, e.g. argv[0].
 * @throws TestFailure on test failure.
 */
void run_test(const char* name);

// includes and headers common to all tests.

#include <climits>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::exception;
using std::logic_error;
using std::runtime_error;
using std::string;


#if __cplusplus >= 201100 || (defined(_MSVC_LANG) && _MSVC_LANG >= 201100)
#define TESTS_USE_CXX11 1
#else
#define TESTS_USE_CXX11 0
#endif

/** Exception to throw if run_test fails. */
class TestFailure : public std::exception
{
  private:
    string msg;

  public:
    TestFailure(const string& msg)
        : msg(msg)
    {
    }

#if TESTS_USE_CXX11
    const char* what() const noexcept
#else
    const char* what() const throw()
#endif
    {
        return msg.c_str();
    }
};

#endif // CASSIUS_TESTING_COMMON_HPP