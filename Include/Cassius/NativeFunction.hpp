#ifndef CASSIUS_INCLUDE_NATIVEFUNCTION_HPP
#define CASSIUS_INCLUDE_NATIVEFUNCTION_HPP

#include <stack>

#include "Value.hpp"

namespace Cassius {

    /** Function pointer to a function exportable for use by scripts.
     *
     * I.e. your function should have the prototype:
     *
     *    NativeFunction::return_type funcname(NativeFunction::argument_type);
     *
     * @see Engine::Register
     */
    class CASSIUS_API NativeFunction
    {
      public:
        /// typedefs to match the C++03 std::unary_function interface
        typedef ValueList result_type;
        typedef ValueList argument_type;

        NativeFunction();
        NativeFunction(const char *name, ValueList (*funcptr)(ValueList));

        ValueList operator()(ValueList values);

        /* Returns the name associated with the function or NULL if invalid.
         */
        inline const char *name() { return name_; }

      private:
        const char *name_;
        ValueList (*func)(ValueList);
    };
}
#endif

