
#include <Cassius/Cassius.hpp>

#include <Cassius/NativeFunction.hpp>

namespace Cassius {

    NativeFunction::NativeFunction()
        : name_(NULL), func(NULL)
    {
    }

    NativeFunction::NativeFunction(const char *name,
                                   result_type (*funcptr)(argument_type))
        : name_(name), func(funcptr)
    {
    }

        #if 0
        NativeFunction(const NativeFunction &other)
        {
            name = other.name;
            func = other.func;
        }
        const NativeFunction &operator=(const NativeFunction &other)
        {
            name = other.name;
            func = other.func;
            return *this;
        }
        #endif

    NativeFunction::result_type
    NativeFunction::operator()(NativeFunction::argument_type values)
    {
        return func(values);
    }


}

