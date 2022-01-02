// SPDX-License-Identifier: ISC
// Copyright 2021, Terry M. Poulin.
/*
 * Tests Cassisus::Value for characters.
 */

#include "./Common.hpp"

#include <Cassius/Value.hpp>

#include <climits>

static void char_test(const Cassius::Value &value, char expected);

static void char_test(const Cassius::Value &value, char expected)
{
    if (value.type() != Cassius::Value::isChar) {
        throw TestFailure("type() != Cassius::Value::isChar");
    }

    if (value.value().asChar != expected) {
        throw TestFailure("value().asChar != expected)");
    }

    if (value.as_integer() != static_cast<int>(expected)) {
        throw TestFailure("as_integer() != expected");
    }
    if (value.as_real() != static_cast<double>(expected)) {
        throw TestFailure("as_real() != expected");
    }
    if (value.as_string() != std::string(1, expected)) {
        throw TestFailure("as_string() != expected");
    }
}

void run_test(const char *name)
{
    for (char ch = CHAR_MIN; ch < CHAR_MAX; ++ch) {
        char_test(Cassius::Value(ch), ch);
    }
}