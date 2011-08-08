#include <iostream>

#include <Cassius/Cassius.hpp>

#include <sstream>
#include <stdexcept>
#include <string>

#include <cassert>
#include <climits>
#include <cstring>

#include <Cassius/CluaEngine.hpp>
#include <Cassius/NativeFunction.hpp>
#include <Cassius/Source.hpp>
#include <Cassius/SourceFile.hpp>

#include "lua.hpp"
#include "funcs.hpp"
#include "debug.hpp"

using std::deque;
using std::invalid_argument;
using std::logic_error;
using std::range_error;
using std::runtime_error;
using std::string;
using std::stringstream;

// Helper that slurps count values off the stack and into a ValueList
static Cassius::ValueList slurpStack(lua_State *interp, int count)
{
    Cassius::ValueList p;
    using Cassius::Value;

    for (int i=0; i < count; ++i) { Value v; int top = lua_gettop(interp);
        switch (lua_type(interp, top)) {
            case LUA_TNONE: {
                // probably an internal error
                stringstream m;
                m << "invalid stack index: "
                  << "lua_type at index "
                  << i << " "
                  << "is LUA_TNONE";
                throw std::runtime_error(m.str());
            }
            // case LUA_TNIL: { //where in the switch I want it to be after it is supported by Value
                // break;
            // }
            case LUA_TNUMBER: {
                //
                // No real way to know whether we should get it as a double or an
                // int, so delegate to the caller and C++ type stuff.
                //
                p.push(Value(static_cast<double>(lua_tonumber(interp, top))));
                //p.push(Value(static_cast<int>(lua_tointeger(interp, top))));
                break;
            }
            case LUA_TBOOLEAN: {
                p.push(Value(lua_toboolean(interp, top)));
                break;
            }
            case LUA_TSTRING: {
                p.push(Value(lua_tostring(interp, top)));
                break;
            }
            case LUA_TNIL: //remove me
            case LUA_TTABLE:
            case LUA_TFUNCTION:
            case LUA_TUSERDATA:
            case LUA_TTHREAD: 
            case LUA_TLIGHTUSERDATA:
            default: {
                stringstream m;
                
                m << "CluaEngine does not YET support converting "
                  << "return values of Lua type "
                  << lua_typename(interp, i)
                  << " to a C++ type";

                throw invalid_argument(m.str());
            }
        }
    }
    lua_pop(interp, count);

    return p;
}

namespace Cassius {

    CluaEngine::CluaEngine()
        : Engine()
    {
        if ((interp = luaL_newstate()) == 0) {
            throw runtime_error("Unable to initialize lua interpretor");
        }
        // Ensure that the standard libraries, like io and string are loaded.
        luaL_openlibs(interp);

        const char *table = "Cassius";

        // Create a table for Cassius
        lua_newtable(interp);
        lua_setglobal(interp, table);

        // export the function proxy() function as Cassius.proxy() for use in
        // exporting Nativefunctions to Lua via our Register() method.
        lua_getglobal(interp, table);
        lua_pushcfunction(interp, &proxy);
        lua_setfield(interp, 1, "proxy");

        // clear the stack
        lua_settop(interp, 0);
        assert(dumpStack(interp) == 0);

        // store a pointer to our mapping table in the Lua registery
        // with the address of the current interpretor as the key.
        lua_pushlightuserdata(interp, (void *)interp);
        lua_pushlightuserdata(interp, (void *)&functions);
        lua_settable(interp, LUA_REGISTRYINDEX);
    }

    CluaEngine::~CluaEngine()
    {
        assert(interp != 0);

        lua_close(interp);
    }

    void CluaEngine::Evaluate(Source &code)
    {
        if (luaL_dostring(interp, code.get().c_str()) != 0) {
            // TODO throw an error
        }

        // for now we ignore return values (oi) and just clear the stack.
        // we can pop the stack empty in order to get the return values
        //
        lua_pop(interp, lua_gettop(interp));
    }

    // needed because the equalvialent code with luaL_dostring and a
    // SourceStream does not work. -- 2011-07-31, Terry P.
    //
    void CluaEngine::Evaluate(SourceFile &code)
    {
        if (luaL_dofile(interp, code.get().c_str())) {
            // TODO throw an error
        }
    }

    bool CluaEngine::Register(NativeFunction func)
    {
        const char *name = func.name();
        if (name == NULL) return false;

        // Create a wrapper function that calls Cassius.proxy()
        //
        // function <name>(...) return Cassius.proxy(<name>, unpack(arg)) end
        //
        string s("function ");
        s.append(name);
        s.append("(...) return Cassius");
        s.append(".proxy(\"");
        s.append(name);
        s.append("\", unpack(arg)) end");

        if (luaL_dostring(interp, s.c_str()) != 0) {
            return false;
        }

        functions.push_back(func);
        return true;
    }

    ValueList CluaEngine::Call(void)
    {
        if (StackSize()-1 != callInfo.nargs) {
            // how should we handle wrong # of arguments? IMHO round to the
            // actual and let Lua error handling settle the rest.
        }
        WITH_STACKDUMP(lua_call(interp, StackSize() - 1, callInfo.nrets));
        return slurpStack(interp, callInfo.nrets);
    }

    void CluaEngine::PushFunction(const char *func, int nrets, int nargs)
    {

        callInfo.nrets = nrets;
        callInfo.nargs = nargs;

        const char *p = std::strchr(func, '.');

        // simple case, func = name of a global function
        if (p == NULL) {
            lua_getglobal(interp, func);
            return;
        }

        throw invalid_argument("CluaEngine::PushFunction does not YET support "
                               "being called with func = \"x.y\" and similar "
                               "constructs. Only global functions are "
                               "supported at this time. Sorry!");
    }

    void CluaEngine::Push(bool b)
    {
        lua_pushboolean(interp, b);
    }

    void CluaEngine::Push(char c)
    {
        lua_pushlstring(interp, &c, 1);
    }

    void CluaEngine::Push(int i)
    {
        lua_pushinteger(interp, i);
    }

    void CluaEngine::Push(double r)
    {
        lua_pushnumber(interp, r);
    }


    void CluaEngine::Push(const char *s)
    {
        lua_pushstring(interp, s);
    }

    void CluaEngine::Pop(size_t n)
    {
        if (n > INT_MAX) {
            throw range_error("Attempt to pop more values than the maximum "
                              "theoretical stack size permitted by Lua.");
        }

        lua_pop(interp, n);
    }

    size_t CluaEngine::StackSize()
    {
        return lua_gettop(interp);
    }

}

extern "C" Cassius::Engine *new_clua(void)
{
    return new Cassius::CluaEngine();
}

extern "C" void delete_clua(Cassius::Engine *obj)
{
    delete obj;
}

