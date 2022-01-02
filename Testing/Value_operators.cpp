// SPDX-License-Identifier: ISC
// Copyright 2022, Terry M. Poulin.
/*
 * Tests operators of Cassisus::Value.
 */

#include "./Common.hpp"

#include <Cassius/Value.hpp>

void run_test(const char* name)
{
    Cassius::Value v;
    if (v.type() != Cassius::Value::isNull) {
        throw TestFailure("Default constructed Value: type() != isNull");
    }

    v = true;
    if (v.type() != Cassius::Value::isBool) {
        throw TestFailure("After operator=(bool) for true: type() != isBool");
    }
    if (v.value().asBool != true) {
        throw TestFailure("After operator=(bool) for true: value() != true");
    }
    v = false;
    if (v.type() != Cassius::Value::isBool) {
        throw TestFailure("After operator=(bool) for false: type() != isBool");
    }
    if (v.value().asBool != false) {
        throw TestFailure("After operator=(bool) for false: value() != false");
    }

    v = 1234;
    if (v.type() != Cassius::Value::isInt) {
        throw TestFailure("After operator=(int): type() != isInt");
    }
    if (v.value().asInt != 1234) {
        throw TestFailure("After operator=(int): value() != expected");
    }

    v = 'x';
    if (v.type() != Cassius::Value::isChar) {
        throw TestFailure("After operator=(char): type() != isChar");
    }
    if (v.value().asChar != 'x') {
        throw TestFailure("After operator=(char): value() != expected");
    }

    v = 5.678;
    if (v.type() != Cassius::Value::isReal) {
        throw TestFailure("After operator=(double): type() != isReal");
    }
    if (v.value().asReal < 5.67 || v.value().asReal > 5.69) {
        throw TestFailure("After operator=(double): value() out of range");
    }

    string cppstr = "Hello, world";
    v = cppstr.c_str();
    if (v.type() != Cassius::Value::isString) {
        throw TestFailure("After operator=(const char*): type() != isString");
    }
    if (strcmp(v.value().asString, cppstr.c_str()) != 0) {
        throw TestFailure("After operator=(const char*): value() != expected");
    }

    int n = 1;
    int* p = &n;
    v = p;
    if (v.type() != Cassius::Value::isPtr) {
        throw TestFailure("After operator=(void*): type() != isPtr");
    }
    int* vp = (int*)v.value().asPtr;
    if (p != vp || *p != *vp) {
        throw TestFailure("After operator=(void*): value() != expected");
    }
}