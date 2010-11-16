#ifndef CASSIUS_INCLUDE_VALUE_HPP
#define CASSIUS_INCLUDE_VALUE_HPP

#include "Cassius.hpp"

namespace Cassius {
    /** Helper class representing a handle to a plain old C++ value.
     *
     * This is principally used by C++ code that needs to give or receive a
     * value from or to a script through Cassius::Engine, e.g. as an argument
     * list or return value.
     *
     * Note bene: that while Value::values contains members for accessing the
     * data as a raw pointer type and as a classic "C-string", this class
     * currently does no memory management of its own on your behave. This is
     * delegated to the client. In lay mens terms, do your own string copying.
     *
     * @see Engine::Register
     */
    class CASSIUS_API Value {
      public:
        enum types { isBool, isChar, isInt, isReal, isString, isPtr };
        union values {
            bool asBool;
            char asChar;
            int asInt;
            double asReal;
            const char *asString;
            void *asPtr;
        };

        Value()                  { /* supplied copy ctor / copy operator=
                                    * should be sufficent for your needs
                                    */
                                 }
        Value(bool b)            { myValue.asBool = b; myType = isBool; }
        Value(int i)             { myValue.asInt = i; myType = isInt; }
        Value(char c)            { myValue.asChar = c; myType = isChar; }
        Value(double d)          { myValue.asReal = d; myType = isReal; }
        Value(const char *s)     { myValue.asString = s; myType = isString; }
        Value(void *p)           { myValue.asPtr = p; myType = isPtr; }

        const inline types type() const { return myType; }
        const inline values value() const { return myValue; }

      private:
        mutable types myType;
        mutable values myValue;
    };
}
#endif

