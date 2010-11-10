#include "../Include/CpythonEngine.hpp"

#include <stdexcept>

// meta header, it's childern should provide the extern "C"'s we need.
#include <Python.h>

namespace Cassius {

    CpythonEngine::CpythonEngine()
        : Engine()
    {
        Py_Initialize();
    }

    CpythonEngine::~CpythonEngine()
    {
        Py_Finalize();
    }

    void
    CpythonEngine::Run(Source &code)
    {
        PyRun_SimpleString(code.get().c_str());
    }
}

extern "C" Cassius::Engine *new_cpython(void) { return new Cassius::CpythonEngine(); }


