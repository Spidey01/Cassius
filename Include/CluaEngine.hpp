#ifndef CASSIUS_INCLUDE_CLUAENGINE_HPP
#define CASSIUS_INCLUDE_CLUAENGINE_HPP

#include "Engine.hpp"
#include "Source.hpp"

#include <lua.hpp>

namespace Cassius {
    class CluaEngine : public Engine {
      public:
        CluaEngine();
        virtual ~CluaEngine();
        virtual void Run(Source &code);

      private:
        CluaEngine(const CluaEngine &other);
        const CluaEngine &operator=(const CluaEngine &other);

        lua_State *interp;
    };
}

extern "C" Cassius::Engine *new_clua(void);

#endif


