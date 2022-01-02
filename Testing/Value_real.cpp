// SPDX-License-Identifier: ISC
// Copyright 2021, Terry M. Poulin.
/*
 * Tests Cassisus::Value for real numbers like double.
 */

#include "./Common.hpp"

#include <Cassius/Value.hpp>

void run_test(const char *name)
{
    Cassius::Value value(2.0);

    if (value.type() != Cassius::Value::isReal) {
        throw TestFailure("type() != isReal");
    }

    double r = value.value().asReal;
    if (r < 1.9 || r > 2.1) {
        throw TestFailure("value().asReal out of range");
    }

    if (value.as_integer() != (int)r) {
        throw TestFailure("asInteger() != (int)r");
    }
}