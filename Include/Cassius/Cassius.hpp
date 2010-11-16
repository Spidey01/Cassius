#ifndef CASSIUS_INCLUDE_CASSIUS_HPP
#define CASSIUS_INCLUDE_CASSIUS_HPP

#if defined(_WIN32) || defined(__WIN64)
#	define CASSIUS_API __declspec(dllexport)
#else
#	define CASSIUS_API /* sane */
#endif

namespace Cassius {

    /**
     * Enumeration of what scripting languages may be used
     */
    enum ScriptLanguages {
        LANG_LUA,
        LANG_PYTHON,
        LANG_ECMASCRIPT,
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
        IMPL_SPIDERMONKEY,
        IMPL_V8,
    };
}
#endif
