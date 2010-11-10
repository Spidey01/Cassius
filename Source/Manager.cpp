
#include "../Include/Manager.hpp"

#include <CxxPlugin.hxx>

namespace Cassius {

    Manager::Manager()
    {
    }

    Manager::~Manager()
    {
    }

    Engine *Manager::CreateEngine(ScriptLanguages lang, Backends impl)
    {
        newengine_fptr_t newengine;

#define LOAD_ENGINE(n, plugname) \
    do { \
        if (!backends. n ) { \
            backends. n = new CxxPlugin((plugname)); \
            backends.new_##n = (newengine_fptr_t)backends. n ->load_funcptr("new_" #n ); \
            if (!backends.new_##n ) { \
                return 0; \
            } \
        } \
    } while (0)


        switch (lang) {
            case LANG_LUA:
                {
                    LOAD_ENGINE(clua, "CassiusCluaEngine");
                    newengine = backends.new_clua;
                    break;
                }
            case LANG_PYTHON:
                {
                    LOAD_ENGINE(cpython, "CassiusCpythonEngine");
                    newengine = backends.new_cpython;
                    break;
                }
            default:
                return 0;
        }

        Engine *e = newengine();
        e->lang = lang;
        e->impl = impl;
        engines.push_back(e);
        return e;
    }

}

