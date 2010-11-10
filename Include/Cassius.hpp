#ifndef CASSIUS_INCLUDE_CASSIUS_HPP
#define CASSIUS_INCLUDE_CASSIUS_HPP

namespace Cassius {

    /**
     * Enumeration of what scripting languages may be used
     */
    enum ScriptLanguages {
        LANG_LUA,
        LANG_PYTHON,
    };

    /**
     * Enumeration of backends that may be embedded.
     *
     * This will eventually be used, to handle situations such as choosing
     * whether Mozilla SpiderMonkey or Google V8 is used as a backend for
     * EcmaScript/JavaScript.
     */
    enum Backends {
        IMPL_DEFAULT,
        IMPL_CLUA,
        IMPL_CPYTHON,
    };
}
#endif
