// SPDX-License-Identifier: ISC
// Copyright 2021, Terry M. Poulin.
/*
 * Tests Cassisus::Value for booleans.
 */

#include "./Common.hpp"

#include <Cassius/Value.hpp>

static void bool_test(const Cassius::Value &value, bool expected);

static void bool_test(const Cassius::Value &value, bool expected)
{
    cout << "Testing value ; expected = " << (expected ? "true" : "false") << endl;

    if (value.type() != Cassius::Value::isBool) {
        throw TestFailure("type() != Cassius::Value::isBool");
    }

    if (value.value().asBool != expected) {
        throw TestFailure("value().asBool != expected)");
    }

    if (value.as_integer() != static_cast<int>(expected)) {
        throw TestFailure("as_integer() != expected");
    }

    if (value.as_real() != static_cast<double>(expected)) {
        throw TestFailure("as_real() != expected");
    }
}

void run_test(const char *name)
{
    bool_test(Cassius::Value(true), true);
    bool_test(Cassius::Value(false), false);
}