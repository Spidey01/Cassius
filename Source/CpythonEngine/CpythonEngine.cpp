// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <iostream>
#include <stdexcept>

#include <Cassius/CpythonEngine.hpp>
#include <Cassius/Source.hpp>

namespace Cassius {

    CpythonEngine::CpythonEngine()
        : Engine()
    {
        Py_Initialize();

        if ((argslist = (PyObject *)PyList_New(0)) == 0) {
            throw std::runtime_error("Unable to create argument vector");
        }
        if (PyImport_AddModule("Cassius") == NULL) {
            throw std::runtime_error("Unable to import Cassius module");
        }
            
    }

    CpythonEngine::~CpythonEngine()
    {
        Py_DECREF(argslist);
        Py_Finalize();
    }

    void CpythonEngine::Evaluate(Source &code)
    {
        PyRun_SimpleString(code.get().c_str());
    }

    bool CpythonEngine::Register(NativeFunction func)
    {
        // not implemented yet
        return false;
    }

    void CpythonEngine::Call(void)
    {
        PyObject *func = PySequence_GetItem(argslist, 0);
        PySequence_DelItem(argslist, 0);
        PyObject_CallObject(func, PySequence_Tuple(argslist));
        Py_DECREF(func);
    }

    void CpythonEngine::PushFunction(const char *name)
    {
		PyObject *func = PyDict_GetItemString(PyModule_GetDict(
		                                      PyImport_AddModule("__main__")),
		                                      name);
        if (!func) {
            Py_DECREF(func);
            throw std::runtime_error("Attempt to push non existant function");
        }
        PyList_Append(argslist, func);
        Py_DECREF(func);
    }

    void CpythonEngine::Push(bool b)
    {
        PyList_Append(argslist, b ? Py_True : Py_False);
    }

    void CpythonEngine::Push(char c)
    {
        PyList_Append(argslist, Py_BuildValue("c", c));
    }

    void CpythonEngine::Push(int i)
    {
        PyList_Append(argslist, Py_BuildValue("i", i));
    }

    void CpythonEngine::Push(double r)
    {
        PyList_Append(argslist, Py_BuildValue("d", r));
    }

    void CpythonEngine::Push(const char *s)
    {
        PyList_Append(argslist, Py_BuildValue("s", s));
    }

    void CpythonEngine::Pop(size_t n)
    {
        throw std::logic_error("not implemented yet");
    }

    size_t CpythonEngine::StackSize()
    {
        return PyList_Size(argslist);
    }
}

extern "C" Cassius::Engine *new_cpython(void) { return new Cassius::CpythonEngine(); }
extern "C" void delete_cpython(Cassius::Engine *obj) { delete obj; }

