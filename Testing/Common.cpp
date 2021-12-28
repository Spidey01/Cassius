// SPDX-License-Identifier: ISC
// Copyright 2021, Terry M. Poulin.
#include "./Common.hpp"

/*
 * Common code linked into each test program.
 *
 * Calls the run_test() to be provided by the test program with a little nicer
 * exception logging and so on.
 */

int main(int argc, char* argv[])
{
    const char* name = argv[0];
    int rc = 1;

    try {
        cout << "Running test " << name << endl;
        run_test(name);
        rc = 0;
    } catch (runtime_error& re) {
        cout << name << ": runtime_error: " << re.what() << endl;
    } catch (exception& ex) {
        cout << name << ": exception: " << ex.what() << endl;
    }

    return rc;
}