#ifndef CASSIUS_INCLUDE_CLUAENGINE_HPP
#define CASSIUS_INCLUDE_CLUAENGINE_HPP

#include <deque>
#include <string>

struct lua_State;

#include "Engine.hpp"

namespace Cassius {

    class CASSIUS_API CluaEngine : public Engine {
      public:
        CluaEngine();
        virtual ~CluaEngine();
        virtual void Evaluate(Source &code);
        virtual void Evaluate(SourceFile &code);
        virtual ValueList Call(void);
        virtual bool Register(NativeFunction func);
        virtual void PushFunction(const char *name, int nrets, int nargs);
        virtual void Push(bool b);
        virtual void Push(char c);
        virtual void Push(int i);
        virtual void Push(double r);
        virtual void Push(const char *s);
        virtual void Pop(size_t n=1);
        virtual size_t StackSize();

      private:
        CluaEngine(const CluaEngine &other);
        const CluaEngine &operator=(const CluaEngine &other);

        lua_State *interp;
        std::deque<NativeFunction> functions;

        struct {
            int nargs;
            int nrets;
        } callInfo;
    };
}

extern "C" Cassius::Engine *new_clua(void);
extern "C" void delete_clua(Cassius::Engine *obj);

#endif

