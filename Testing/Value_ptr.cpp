// SPDX-License-Identifier: ISC
// Copyright 2021, Terry M. Poulin.
/*
 * Tests Cassisus::Value for pointers.
 */

#include "./Common.hpp"

#include <Cassius/Value.hpp>

void run_test(const char *name)
{
    long deadbeef = 0xDEADBEEF;
    long* ptr = &deadbeef;

    Cassius::Value value((void*)ptr);

    if (value.type() != Cassius::Value::isPtr) {
        throw TestFailure("type() != Cassius::Value::isBool");
    }

    long* v = (long*)value.value().asPtr;

    if (v != ptr) {
        throw TestFailure("value().asPtr != expected)");
    }

    if (*v != *ptr) {
        throw TestFailure("*value().asPtr != *expected)");
    }
}