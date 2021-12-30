#ifndef CASSIUS_INCLUDE_CASSIUS_HPP
#define CASSIUS_INCLUDE_CASSIUS_HPP
// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

/**
 * @brief Generated by cmake's GenerateExportHeader module.
 *
 * Provides the macros:
 *
 * - CASSIUS_EXPORT
 * - CASSIUS_NO_EXPORT
 * - CASSIUS_DEPRECATED
 * - CASSIUS_DEPRECATED_EXPORT
 * - CASSIUS_DEPRECATED_NO_EXPORT
 * 
 * @see https://cmake.org/cmake/help/latest/module/GenerateExportHeader.html
 */
#include <Cassius/cassius_export.hpp>

#define CASSIUS_API CASSIUS_EXPORT

#include <cstddef>

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

