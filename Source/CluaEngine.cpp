
#include "../Include/CluaEngine.hpp"

#include <stdexcept>

#include <cassert>

namespace Cassius {

    CluaEngine::CluaEngine()
        : Engine()
    {
        if ((interp = luaL_newstate()) == 0) {
            throw std::runtime_error("Cassius::CluaEngine -> Unable to initialize lua interpretor");
        }
        // Ensure that the standard libraries, like io and string are loaded.
        luaL_openlibs(interp);
    }

    CluaEngine::~CluaEngine()
    {
        assert(interp != 0);

        lua_close(interp);
    }

    void
    CluaEngine::Run(Source &code)
    {
        luaL_dostring(interp, code.get().c_str());
    }
}

extern "C" Cassius::Engine *new_clua(void) { return new Cassius::CluaEngine(); }

