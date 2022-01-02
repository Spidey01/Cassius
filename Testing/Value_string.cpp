// SPDX-License-Identifier: ISC
// Copyright 2021, Terry M. Poulin.
/*
 * Tests Cassisus::Value for strings.
 */

#include "./Common.hpp"

#include <Cassius/Value.hpp>

#include <cstring>

static void string_test(const Cassius::Value& value, const string& expected);

static void string_test(const Cassius::Value& value, const string& expected)
{
    cout << "Testing value " << value.value().asString << "; expected = " << expected << endl;

    if (value.type() != Cassius::Value::isString) {
        throw TestFailure("type() != Cassius::Value::isString");
    }

    const char *s = value.value().asString;
    if (std::strcmp(s, expected.c_str()) != 0) {
        throw TestFailure("value().asString != expected)");
    }

    if (value.as_integer() != std::atoi(expected.c_str())) {
        throw TestFailure("as_integer() != atoi(expected)");
    }

    if (value.as_real() != std::atof(expected.c_str())) {
        throw TestFailure("as_real() != atof(expected)");
    }

    if (value.as_string() != expected) {
        throw TestFailure("as_string() != expected");
    }
}

void run_test(const char* name)
{
    string hello = "Hello, World!";
    string_test(Cassius::Value(hello.c_str()), hello);
}