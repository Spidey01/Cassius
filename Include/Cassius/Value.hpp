#ifndef CASSIUS_INCLUDE_VALUE_HPP
#define CASSIUS_INCLUDE_VALUE_HPP
// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <Cassius/Cassius.hpp>
#include <stack>

namespace Cassius
{
    /** Helper class representing a handle to a plain old C++ value.
     *
     * This is principally used by C++ code that needs to give or receive a
     * value from or to a script through Cassius::Engine, e.g. as an argument
     * list or return value.
     *
     * Note bene: that while Value::values contains members for accessing the
     * data as a raw pointer type and as a classic "C-string", this class
     * currently does no memory management of its own on your behalf. This is
     * delegated to the client. In lay mens terms, do your own string copying.
     *
     * @see Engine::Register
     */
    class CASSIUS_API Value
    {
      public:
        ///
        /// Enumeration of the types a Value can contain.
        ///
        enum types {
            isNull,   ///< No type or value. Default initialized.
            isBool,   ///< Contains boolean type.
            isChar,   ///< Contains character type.
            isInt,    ///< Contains integeral type.
            isReal,   ///< Contains floating point type.
            isString, ///< Contains string type.
            isPtr,    ///< Contains a pointer type. Not recommended.
        };

        ///
        /// Union for accessing the raw value.
        ///
        /// Never access this unless type() returns the corrisponding types
        /// enum.
        ///
        union values {
            bool asBool;
            char asChar;
            int asInt;
            double asReal;
            const char* asString;
            void* asPtr;
        };

        Value();
        Value(const Value& other);
        Value(bool b);
        Value(int i);
        Value(char c);
        Value(double d);
        Value(const char* s);
        Value(void* p);

        const inline types type() const { return mType; }
        const inline values value() const { return mValue; }

        Value& operator=(const Value& other);
        Value& operator=(bool b);
        Value& operator=(int i);
        Value& operator=(char c);
        Value& operator=(double d);
        Value& operator=(const char* s);
        Value& operator=(void* p);

      private:
        types mType;
        values mValue;
    };

    typedef std::stack<Value> ValueList;
} // namespace Cassius
#endif
