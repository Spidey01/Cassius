#ifndef CASSIUS_INCLUDE_ENGINE_HPP
#define CASSIUS_INCLUDE_ENGINE_HPP

#include "Cassius.hpp"
#include "NativeFunction.hpp"

namespace Cassius {
    class Source;

    class CASSIUS_API Engine {
      public:
        Engine() {}
        virtual ~Engine() {};
        virtual void Evaluate(Source &code) = 0;

        /**  Register a NativeFunction for use by scripts
         *
         * @see Cassius::NativeFunction
         */
        virtual bool Register(NativeFunction func) = 0;

        /** call func with empty parameter list */
        virtual void Call(const char *func);

        /** call using the current stack state */
        virtual void Call(void) = 0;

        virtual void PushFunction(const char *name) = 0;
        virtual void Push(bool b) = 0;
        virtual void Push(char c) = 0;
        virtual void Push(int i) = 0;
        virtual void Push(double r) = 0;
        virtual void Push(const char *s)  = 0;

        /** Pop stack frames
         *
         * @param n number of frames to pop, default is 1
         */
        virtual void Pop(size_t n=1) = 0;

        /** Current size of the stack */
        virtual size_t StackSize() = 0;

        ScriptLanguages lang;
        Backends impl;

        /* Template code generated by premake4 */
        #include "Engine.tpp"

      private:
        Engine(const Engine &other);
        const Engine &operator=(const Engine &other);
    };
}

#endif

