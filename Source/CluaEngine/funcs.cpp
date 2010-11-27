
#include <Cassius/Cassius.hpp>

#include <cstdlib>
#include <cstring>

#include <deque>

#include <Cassius/CluaEngine.hpp>
#include <Cassius/NativeFunction.hpp>

using std::strcmp;

using std::deque;

using Cassius::NativeFunction;
using Cassius::Value;


void die(lua_State *interp, const char *e)
{
    lua_pushstring(interp, e);
    lua_error(interp);
    std::abort();
}


#ifndef NDEBUG
#include <iostream>
#endif
void dumpStack(lua_State *interp)
{
#ifndef NDEBUG
    std::cout << "frame count " << lua_gettop(interp) << std::endl;
    for (int i=lua_gettop(interp); i > 0; --i) {
        std::cout << "stack frame " << i << " is" 
                  << lua_typename(interp, lua_type(interp, i))
                  << std::endl;
    }
    std::cout << "end of frames" << std::endl;
#endif
}

NativeFunction getRealFunctor(lua_State *interp, const char *realName)
{
    // Aquire a pointer to the CluaEngine's private functions object that was
    // registered by its ctor.
    //
    lua_pushlightuserdata(interp, (void *)interp);
    lua_gettable(interp, LUA_REGISTRYINDEX);

    typedef deque<NativeFunction> FunctionsList;

    FunctionsList *functions =
        static_cast<FunctionsList*>(lua_touserdata(interp, -1));

    for (FunctionsList::iterator it = functions->begin();
         it != functions->end(); *it++)
    {
        NativeFunction f = *it;
        const char *name = f.name();
        if (name != NULL && strcmp(name, realName) == 0) {
            return f;
        }
    }
    // not found.
    return NativeFunction(NULL, NULL);
}

void toValueStack(lua_State *interp,
                  NativeFunction::argument_type &args,
                  int nargs)
{
#define ISTYPE(t) lua_is##t (interp, i)
#define PUSHARG(f) do { args.push( lua_to##f (interp, i) ); } while (0)
    for (int i=1; i <= nargs; ++i) {
        if (ISTYPE(cfunction) || ISTYPE(thread) || ISTYPE(userdata)) {
            die(interp, "unable to convert argument");
        }
        else if (ISTYPE(boolean)) PUSHARG(boolean);
        //
        // In Lua, this should always come back as a double.
        // It is also possible that the user has changed LUA_NUMBER
        // in which case it is on their own head if the value is FUBAR.
        //
        else if (ISTYPE(number)) PUSHARG(number);
        else if (ISTYPE(string)) PUSHARG(string);
        else {
            die(interp, "bad argument");
        }
    }
#undef PUSHARG
#undef ISTYPE
}

void pushValueStack(lua_State *interp, NativeFunction::argument_type &values)
{
    while (!values.empty()) {
        Value v = values.top();
        values.pop();

        switch (v.type()) {
            case Value::isBool:
                lua_pushboolean(interp, v.value().asBool);
                break;
            case Value::isInt:
                lua_pushinteger(interp, v.value().asInt);
                break;
            case Value::isReal:
                lua_pushnumber(interp, v.value().asReal);
                break;
            case Value::isString:
                lua_pushstring(interp, v.value().asString);
                break;
            case Value::isChar:
            case Value::isPtr:
            default:
                die(interp, "unable to convert return value");
        }
    }
}

int proxy(lua_State *interp)
{
    if (!interp) return 0;

    // CluaEngine::Register() generated wrapper functions call us with the
    // name the user gave to Register(), placed at the top of the stack.
    // Any other behaviour is an error.
    //
    int nargs = lua_gettop(interp);
    if (nargs < 1) {
        luaL_error(interp, "Cassius.proxy called with invalid function name");
    }

    const char *realname = lua_tostring(interp, 1); --nargs;
    NativeFunction realfunc = getRealFunctor(interp, realname);
    NativeFunction::argument_type args, returns;

    toValueStack(interp, args, nargs);
    returns = realfunc(args);
    pushValueStack(interp, returns);
    return returns.size();
}

