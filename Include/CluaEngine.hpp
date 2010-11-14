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
        virtual void Call(void);
        virtual void PushFunction(const char *name);
        virtual void Push(char c);
        virtual void Push(int i);
        virtual void Push(double r);
        virtual void Push(const char *s);
        virtual void Pop(size_t n=1);
        virtual size_t StackSize();

        /* Call() template code shared with class Engine */
        #include "Engine.tpp"

      private:
        CluaEngine(const CluaEngine &other);
        const CluaEngine &operator=(const CluaEngine &other);

        lua_State *interp;
        size_t stacksize;
        int nargs;
    };
}

extern "C" Cassius::Engine *new_clua(void);
extern "C" void delete_clua(Cassius::Engine *obj);

#endif

