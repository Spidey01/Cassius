#ifndef CASSIUS_INCLUDE_CPYTHONENGINE_HPP
#define CASSIUS_INCLUDE_CPYTHONENGINE_HPP

// Meta header for Pythons C API, it's childern should provide the extern "C"'s we need.
// The docs say it should come before all standard headers.
#include <Python.h>

#include "Engine.hpp"
#include "Source.hpp"

namespace Cassius {
    class CASSIUS_API CpythonEngine : public Engine {
      public:
        CpythonEngine();
        virtual ~CpythonEngine();
        virtual void Run(Source &code);
        virtual void Call(void);
        virtual void PushFunction(const char *name);
        virtual void Push(bool b);
        virtual void Push(char c);
        virtual void Push(int i);
        virtual void Push(double r);
        virtual void Push(const char *s);
        virtual void Pop(size_t n=1);
        virtual size_t StackSize();

        /* Call() template code shared with class Engine */
        #include "Engine.tpp"

      private:
        CpythonEngine(const CpythonEngine &other);
        const CpythonEngine &operator=(const CpythonEngine &other);

        PyObject *argslist;
    };
}

extern "C" Cassius::Engine *new_cpython(void);
extern "C" void delete_cpython(Cassius::Engine *obj);

#endif

