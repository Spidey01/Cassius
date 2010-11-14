
#include <cassert>

#include <stdexcept>

#include <CxxPlugin.hxx>

#include <Cassius/Manager.hpp>

using std::list;
using std::runtime_error;

namespace Cassius {

    Manager::Manager()
    {
    }

    Manager::~Manager()
    {
        list<Engine *>::iterator it;

        for (it=engines.begin(); it != engines.end(); ++it) {
            deleteengine_fptr_t delete_engine;

            switch ((*it)->lang) {
                case LANG_LUA:
                    assert(backends.delete_clua != 0);
                    delete_engine = backends.delete_clua;
                    break;
                case LANG_PYTHON:
                    assert(backends.delete_cpython != 0);
                    delete_engine = backends.delete_cpython;
                    break;
                default:
                    // NOTREACHED
                    throw runtime_error( "Cassius::Manager -> "
                                              "Attempt to delete an unknown"
                                              "type script engine.");
                    break;
            }
            delete_engine(*it);
        }
    }

    Engine *Manager::CreateEngine(ScriptLanguages lang, Backends impl)
    {
        newengine_fptr_t newengine;

#define LOAD_ENGINE(n, plugname) \
    do { \
        if (!backends. n ) { \
            backends. n = new CxxPlugin((plugname)); \
            backends.new_##n = (newengine_fptr_t)backends. n ->load_funcptr("new_" #n ); \
            backends.delete_##n = (deleteengine_fptr_t)backends. n ->load_funcptr("delete_" #n ); \
            if ( (!backends.new_##n ) || (!backends.delete_##n ) ) { \
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

