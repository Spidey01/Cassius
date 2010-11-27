
#include <Cassius/Cassius.hpp>

#include <stdexcept>
#include <string>

#include <cassert>
#include <climits>
#include <cstring>

#include <Cassius/CluaEngine.hpp>
#include <Cassius/NativeFunction.hpp>
#include <Cassius/Source.hpp>

#include "funcs.hpp"

using std::deque;
using std::invalid_argument;
using std::logic_error;
using std::range_error;
using std::runtime_error;
using std::string;

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
        dumpStack(interp);

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
    }

    bool CluaEngine::Register(NativeFunction func)
    {
        const char *name = func.name();
        if (name == NULL) return false;

        // Create a wrapper function that calls Cassius.proxy()
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

    void CluaEngine::Call(void)
    {
        dumpStack(interp);
        lua_call(interp, StackSize() - 1, 0);
    }

    void CluaEngine::PushFunction(const char *func)
    {
        const char *p = std::strchr(func, '.');

        // simple case, func = name of a global function
        if (p == NULL) {
            lua_getfield(interp, LUA_GLOBALSINDEX, func);
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

