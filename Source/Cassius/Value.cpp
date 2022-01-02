// SPDX-License-Identifier: ISC
// Copyright 2010,2022 Terry M. Poulin.

#include <Cassius/Value.hpp>

namespace Cassius
{
    Value::Value()
        : mType(isNull)
        , mValue()
    {
        /* Poorly handled. */
    }

    Value::Value(const Value& other)
        : mType(other.mType)
        , mValue(other.mValue)
    {
    }

    Value::Value(bool b)
    {
        mValue.asBool = b;
        mType = isBool;
    }

    Value::Value(int i)
    {
        mValue.asInt = i;
        mType = isInt;
    }

    Value::Value(char c)
    {
        mValue.asChar = c;
        mType = isChar;
    }

    Value::Value(double d)
    {
        mValue.asReal = d;
        mType = isReal;
    }

    Value::Value(const char* s)
    {
        mValue.asString = s;
        mType = isString;
    }

    Value::Value(void* p)
    {
        mValue.asPtr = p;
        mType = isPtr;
    }

    Value& Value::operator=(const Value& other)
    {
        if (this == &other)
            return *this;
        mValue = other.mValue;
        mType = other.mType;
        return *this;
    }

    Value& Value::operator=(bool b)
    {
        mValue.asBool = b;
        mType = isBool;
        return *this;
    }

    Value& Value::operator=(int i)
    {
        mValue.asInt = i;
        mType = isInt;
        return *this;
    }

    Value& Value::operator=(char c)
    {
        mValue.asChar = c;
        mType = isChar;
        return *this;
    }

    Value& Value::operator=(double d)
    {
        mValue.asReal = d;
        mType = isReal;
        return *this;
    }

    Value& Value::operator=(const char* s)
    {
        mValue.asString = s;
        mType = isString;
        return *this;
    }

    Value& Value::operator=(void* p)
    {
        mValue.asPtr = p;
        mType = isPtr;
        return *this;
    }

} // namespace Cassius
