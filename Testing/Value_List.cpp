// SPDX-License-Identifier: ISC
/* Copyright 2021, the Cassius authors. */
/*
 * Tests Cassisus::ValueList.
 */

#include "./Common.hpp"

#include <Cassius/Value.hpp>

#include <climits>

void test_item(Cassius::ValueList& list, const Cassius::Value& item);

void test_item(Cassius::ValueList& list, const Cassius::Value& item)
{
    cout
        << "test_item():"
        << " list.size(): " << list.size()
        << " list.top().type(): " << (int)list.top().type()
        << " item.type(): " << (int)item.type()
        << endl;

    if (list.top().type() != item.type())
        throw TestFailure("list.top().type() != item.type()");

    Cassius::Value::values v = list.top().value();
    Cassius::Value::values i = item.value();
    string bad;

    switch (item.type()) {
        case Cassius::Value::isBool:
            if (v.asBool != i.asBool)
                bad = "wrong boolean value";
            break;
        case Cassius::Value::isInt:
            if (v.asInt != i.asInt)
                bad = "wrong integeral value";
            break;
        case Cassius::Value::isChar:
            if (v.asChar != i.asChar)
                bad = "wrong character value";
            break;
        case Cassius::Value::isReal:
            if (v.asReal != i.asReal)
                bad = "wrong floating point value";
            break;
        case Cassius::Value::isPtr:
            if (v.asPtr != i.asPtr)
                bad = "wrong pointer value";
            break;
        case Cassius::Value::isString:
            if (v.asString != i.asString)
                bad = "wrong string value";
            break;
        default:
            throw logic_error("test_item() switch/case out of date in Value_List.cpp.");
    }

    if (!bad.empty())
        throw TestFailure(bad);

    list.pop();
}

void run_test(const char* name)
{
    Cassius::Value b_true(true);
    Cassius::Value b_false(false);
    Cassius::Value i_min(INT_MIN);
    Cassius::Value i_max(INT_MAX);
    Cassius::Value d_low(1.9);
    Cassius::Value d_high(2.1);
    string hello = "Hello";
    Cassius::Value s_hello(hello.c_str());
    Cassius::Value p_hello((void*)hello.c_str());

    Cassius::ValueList stack;
    stack.push(b_true);
    stack.push(b_false);
    stack.push(i_min);
    stack.push(i_max);
    stack.push(d_low);
    stack.push(d_high);
    stack.push(s_hello);
    stack.push(p_hello);

    Cassius::ValueList other = stack;
    test_item(other, p_hello);
    test_item(other, s_hello);
    test_item(other, d_high);
    test_item(other, d_low);
    test_item(other, i_max);
    test_item(other, i_min);
    test_item(other, b_false);
    test_item(other, b_true);
}