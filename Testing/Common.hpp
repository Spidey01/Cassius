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

using std::cout;
using std::endl;
using std::exception;
using std::logic_error;
using std::runtime_error;
using std::string;

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

#if __cplusplus < 201100
    const char* what() const throw()
#else
    const char* what() const noexcept
#endif
    {
        return msg.c_str();
    }
};

#endif // CASSIUS_TESTING_COMMON_HPP