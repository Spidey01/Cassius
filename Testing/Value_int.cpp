// SPDX-License-Identifier: ISC
// Copyright 2021, Terry M. Poulin.
/*
 * Tests Cassisus::Value for integer numbers like int.
 */

#include "./Common.hpp"

#include <Cassius/Value.hpp>

void run_test(const char *name)
{
    Cassius::Value value(2 + 2);

    if (value.type() != Cassius::Value::isInt) {
        throw TestFailure("type() != isInt");
    }

    int i = value.value().asInt;
    if (i != 4) {
        throw TestFailure("value().asInt is not 4");
    }

    if (value.as_integer() != 4) {
        throw TestFailure("as_integer() is not 4");
    }
    if (value.as_real() < 3.9 || value.as_real() > 4.1) {
        throw TestFailure("as_real() is out of range");
    }
}
