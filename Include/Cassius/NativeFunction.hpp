#ifndef CASSIUS_INCLUDE_NATIVEFUNCTION_HPP
#define CASSIUS_INCLUDE_NATIVEFUNCTION_HPP

#include <functional>
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
        : public std::unary_function< std::stack<Value>, std::stack<Value> >
    {
      public:

        NativeFunction();
        NativeFunction(const char *name, result_type (*funcptr)(argument_type));

        result_type operator()(argument_type values);

        /* Returns the name associated with the function or NULL if invalid.
         */
        inline const char *name() { return name_; }

      private:
        const char *name_;
        result_type (*func)(argument_type);
    };
}
#endif

