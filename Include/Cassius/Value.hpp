#ifndef CASSIUS_INCLUDE_VALUE_HPP
#define CASSIUS_INCLUDE_VALUE_HPP
// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <Cassius/Cassius.hpp>
#include <stack>
#include <string>

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

        /**
         * @brief Access as if type was isInt.
         * 
         * @returns value converted to integer.
         */
        int as_integer() const;

        /**
         * @brief Access as if type was isReal.
         * 
         * @returns value converted to double.
         */
        double as_real() const;

        /**
         * @brief Access as if type was isString.
         * 
         * While most types have some logical conversion (e.g. 1234 to "1234"),
         * the exact representation may vary for given types and should be
         * regarded to change without notice. Such as converting a pointers or
         * booleans to a string.
         * 
         * @returns value converted to string.
         */
        std::string as_string() const;

        /**
         * @brief Template based conversion.
         * 
         * @tparam T must be one of the provided specializations.
         * 
         * @returns value converted to T.
         */
        template <class T>
        inline T get() const;

      private:
        types mType;
        values mValue;
    };

    // template <class T>
    // T Value::get() const
    // {
    //     throw std::logic_error("No default conversion");
    // }

    template <>
    inline int Value::get<int>() const
    {
        return as_integer();
    }

    template <>
    inline double Value::get<double>() const
    {
        as_real();
    }

    template <>
    inline std::string Value::get<std::string>() const
    {
        return as_string();
    }

    typedef std::stack<Value> ValueList;
} // namespace Cassius
#endif
