#ifndef CASSIUS_INCLUDE_SCRIPTFUNCTION_HPP
#define CASSIUS_INCLUDE_SCRIPTFUNCTION_HPP
// SPDX-License-Identifier: ISC
// Copyright 2022, Terry M. Poulin.

#include <Cassius/Cassius.hpp>
#include <Cassius/Engine.hpp>
#include <Cassius/cxxversion.hpp>
#include <Cassius/stdheaders.hpp>

namespace Cassius
{
#if Cassius_CXX14

    /**
     * @brief Alias around std::function<>.
     * 
     * @tparam Args passed to std::function.
     * 
     * @see make_scriptfunction().
     */
    template <class... Args>
    using ScriptFunction = std::function<Args...>;

    /**
     * @brief Make wrapper around a script function.
     * 
     * Use this to wrap a function from a script in a std::function. Thus making
     * it a lot more like a C++ function.
     * 
     * @tparam ReturnValue the scalar return value from the script fuction.
     * 
     * @tparam Args argument pack to the script function.
     * 
     * @param engine the script engine for the call.
     * 
     * @param name the name of the script fuction to call.
     * 
     * @returns Function wrapper that executes the specified script function.
     */
    template <class ReturnValue, class... Args>
    ScriptFunction<ReturnValue(Args...)> make_scriptfunction(Cassius::Engine* engine, const char* name)
    {
        return [engine, name](Args... args) -> ReturnValue {
            int nargs = sizeof...(args);
            engine->PushFunction(name, 1, nargs);

            auto initlist = {args...};
            for (auto it = initlist.begin(); it != initlist.end(); ++it) {
                engine->Push(*it);
            }

            Cassius::ValueList results = engine->Call();
            return results.top().get<ReturnValue>();
        };
    }

#endif
} // namespace Cassius

#endif // CASSIUS_INCLUDE_SCRIPTFUNCTION_HPP