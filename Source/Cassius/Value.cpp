// SPDX-License-Identifier: ISC
// Copyright 2010,2022 Terry M. Poulin.

#include <Cassius/Value.hpp>
#include <cstdint>
#include <stdexcept>

using std::logic_error;

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

    int Value::as_integer() const
    {
        switch (mType) {
            case isNull:
                return 0;
            case isBool:
                return mValue.asBool;
            case isChar:
                return mValue.asChar;
            case isInt:
                return mValue.asInt;
            case isReal:
                return (int)mValue.asReal;
            case isString:
                return std::atoi(mValue.asString);
            case isPtr:
                // CRINGE!!!
                return (int)(intptr_t)mValue.asPtr;
            default:
                throw logic_error("Value::as_integer(): no type()");
        }
    }

    double Value::as_real() const
    {
        switch (mType) {
            case isNull:
                return 0.0;
            case isBool:
                return mValue.asBool;
            case isChar:
                return mValue.asChar;
            case isInt:
                return (double)mValue.asInt;
            case isReal:
                return mValue.asReal;
            case isString:
                return std::atof(mValue.asString);
            case isPtr:
                return (double)(intptr_t)mValue.asPtr;
            default:
                throw logic_error("Value::as_real(): no type()");
        }
    }
} // namespace Cassius
