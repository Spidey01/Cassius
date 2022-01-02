// SPDX-License-Identifier: ISC
// Copyright 2021, Terry M. Poulin.
/*
 * Tests Cassisus::SourceString.
 */

#include "./Common.hpp"

#include <Cassius/SourceString.hpp>

void run_test(const char *name)
{
    string hello = "Hello";

    Cassius::SourceString src(hello.c_str(), hello.size());

    if (src.get() != hello)
        throw TestFailure("src.get() != expected");

    Cassius::SourceString copyAssigned = src;
    if (copyAssigned.get() != hello)
        throw TestFailure("copyAssigned.get() != expected");

    Cassius::SourceString copyConstructed = src;
    if (copyConstructed.get() != hello)
        throw TestFailure("copyConstructed.get() != expected");

    if (src != copyConstructed || src != copyAssigned)
        throw TestFailure("Operator != failure");
    if (!(src == copyConstructed) || !(src == copyAssigned))
        throw TestFailure("Operator == failure");

#if Cassius_CXX11
    Cassius::SourceString moveAssigned = std::move(copyAssigned);
    if (moveAssigned.get() != hello)
        throw TestFailure("moveAssigned.get() != expected");

    Cassius::SourceString moveConstructed = std::move(copyConstructed);
    if (moveConstructed.get() != hello)
        throw TestFailure("moveConstructed.get() != expected");
#endif

}
