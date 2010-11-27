#ifndef CASSIUS_SOURCE_CLUAENGINE_FUNCS_HPP
#define CASSIUS_SOURCE_CLUAENGINE_FUNCS_HPP

#include <Cassius/CluaEngine.hpp>
#include <Cassius/NativeFunction.hpp>

// proxy function that wraps a registered function on the C side of the call.
//
int proxy(lua_State *interp);

// Pushes the stack of Value objects onto the Lua stack
//
// @param interp The lua state to work on.
// @param values Reference to the C++ values to push.
//
void pushValueStack(lua_State *interp,
                    Cassius::NativeFunction::argument_type &values);

// Converts values on the Lua stack for use with a NativeFunction
//
// @param args A reference to the stack to populate
// @param nargs The number of values to pop off the Lua stack
//
// In the event of an error, terminates the program after signaling an error
// through lua_error.
//
void toValueStack(lua_State *interp,
                  Cassius::NativeFunction::argument_type &args,
                  int nargs);

// Gets the registered functor for realName
//
// @param interp The Lua interpretor in this context.
// @param realName The name of the function to look up.
//
// @returns A NativeFunction object corrisponding to the one Registered() for
//          realName. Other wise an empty NativeFunctor with its name field
//          set to NULL.
//
Cassius::NativeFunction getRealFunctor(lua_State *interp, const char *realName);

// Helper to dump the current lua stack to standard out.
// This does nothing if NDEBUG is defined.
//
void dumpStack(lua_State *interp);

// Helper to forcefully quit the applicat yet respect lua_error() behaviour.
// This calls abort to ensure that the program terminates.
//
void die(lua_State *interp, const char *e);

#endif

