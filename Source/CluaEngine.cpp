
#include "../Include/CluaEngine.hpp"

#include <stdexcept>

#include <cassert>
#include <cstdarg>
#include <climits>

#include <cstdio>

using std::runtime_error;
using std::logic_error;
using std::range_error;

#define UPDATE_COUNTERS stacksize++; nargs++

namespace Cassius {

    CluaEngine::CluaEngine()
        : Engine(), stacksize(0), nargs(0)
    {
        if ((interp = luaL_newstate()) == 0) {
            throw runtime_error(
               "Cassius::CluaEngine -> Unable to initialize lua interpretor");
        }
        // Ensure that the standard libraries, like io and string are loaded.
        luaL_openlibs(interp);
    }

    CluaEngine::~CluaEngine()
    {
        assert(interp != 0);

        lua_close(interp);
    }

    void CluaEngine::Run(Source &code)
    {
        luaL_dostring(interp, code.get().c_str());
    }

    void CluaEngine::Call(void)
    {
        if (stacksize > 0 && nargs > (stacksize - 1)) {
            throw logic_error("CluaEngine::Call() -> internal data is FUBAR");
        }
        lua_call(interp, nargs, 0);
        stacksize = 0;
        nargs = 0;
    }

    void CluaEngine::PushFunction(const char *func)
    {
        lua_getfield(interp, LUA_GLOBALSINDEX, func);
        stacksize++;
    }

    void CluaEngine::Push(bool b)
    {
        lua_pushboolean(interp, b);
        UPDATE_COUNTERS;
    }

    void CluaEngine::Push(char c)
    {
        lua_pushlstring(interp, &c, 1);
        UPDATE_COUNTERS;
    }

    void CluaEngine::Push(int i)
    {
        lua_pushinteger(interp, i);
        UPDATE_COUNTERS;
    }

    void CluaEngine::Push(double r)
    {
        lua_pushnumber(interp, r);
        UPDATE_COUNTERS;
    }


    void CluaEngine::Push(const char *s)
    {
        lua_pushstring(interp, s);
        UPDATE_COUNTERS;
    }

    void CluaEngine::Pop(size_t n)
    {
        if (n > INT_MAX) {
            throw range_error(
                "CluaEngine::Pop(n) -> n is larger than Lua's max stack size.");
        }

        lua_pop(interp, n);
    }

    size_t CluaEngine::StackSize() { return stacksize; }
}

extern "C" Cassius::Engine *new_clua(void) { return new Cassius::CluaEngine(); }
extern "C" void delete_clua(Cassius::Engine *obj) { delete obj; }

