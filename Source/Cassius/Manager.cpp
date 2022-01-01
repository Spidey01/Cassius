// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <cassert>

#include <stdexcept>

#include <CxxPlugin.hxx>

#include <Cassius/Manager.hpp>

using std::list;
using std::runtime_error;

namespace Cassius
{

    Manager::Manager()
    {
        backends.clua = 0;
        backends.new_clua = 0;
        backends.delete_clua = 0;

        backends.cpython = 0;
        backends.new_cpython = 0;
        backends.delete_cpython = 0;

        backends.spidermonkey = 0;
        backends.new_spidermonkey = 0;
        backends.delete_spidermonkey = 0;

        backends.v8 = 0;
        backends.new_v8 = 0;
        backends.delete_v8 = 0;
    }

    Manager::~Manager()
    {
        list<Engine*>::iterator it;

        for (it = engines.begin(); it != engines.end(); ++it) {
            deleteengine_fptr_t delete_engine = 0;

            switch ((*it)->lang) {
                case LANG_LUA:
                    assert(backends.delete_clua != 0);
                    delete_engine = backends.delete_clua;
                    break;
                case LANG_PYTHON:
                    assert(backends.delete_cpython != 0);
                    delete_engine = backends.delete_cpython;
                    break;
                case LANG_ECMASCRIPT:
                    switch ((*it)->impl) {
                        case IMPL_SPIDERMONKEY:
                            assert(backends.delete_spidermonkey != 0);
                            delete_engine = backends.delete_spidermonkey;
                            break;
                        case IMPL_V8:
                            assert(backends.delete_v8 != 0);
                            delete_engine = backends.delete_v8;
                            break;
                        default:
                            break;
                    }
                default:
                    // TODO some way of logging this and prevent the delete.
                    // This will be NOTREACHED when valid enum values are given.
                    break;
            }
            if (delete_engine) {
                delete_engine(*it);
            }
        }
    }

    Engine* Manager::CreateEngine(ScriptLanguages lang, Backends impl)
    {
        newengine_fptr_t newengine;

#define LOAD_ENGINE(n, plugname)                                                               \
    do {                                                                                       \
        if (!backends.n) {                                                                     \
            backends.n = new CxxPlugin((plugname));                                            \
            backends.new_##n = (newengine_fptr_t)backends.n->load_funcptr("new_" #n);          \
            backends.delete_##n = (deleteengine_fptr_t)backends.n->load_funcptr("delete_" #n); \
            if ((!backends.new_##n) || (!backends.delete_##n)) {                               \
                return 0;                                                                      \
            }                                                                                  \
        }                                                                                      \
    } while (0)

        switch (lang) {
            case LANG_LUA: {
                LOAD_ENGINE(clua, "CassiusCluaEngine");
                newengine = backends.new_clua;
                break;
            }
            case LANG_PYTHON: {
                LOAD_ENGINE(cpython, "CassiusCpythonEngine");
                newengine = backends.new_cpython;
                break;
            }
            case LANG_ECMASCRIPT:
                switch (impl) {
                    case IMPL_SPIDERMONKEY: {
                        LOAD_ENGINE(spidermonkey,
                                    "CassiusSpiderMonkeyEngine");
                        newengine = backends.new_spidermonkey;
                        break;
                    }
                    case IMPL_V8: {
                        LOAD_ENGINE(v8, "CassiusV8Engine");
                        newengine = backends.new_v8;
                        break;
                    }
                    default:
                        return 0; // wrong impl
                }
                break;
            default:
                return 0;
        }

        Engine* e = newengine();
        //
        // Technically failure here should result in a bad_alloc being thrown.
        // Between Windows, Users, and Typos, better to be safe than SIGSEGSRY.
        //
        if (!e) {
            return 0;
        }
        e->lang = lang;
        e->impl = impl;
        engines.push_back(e);
        return e;
    }

} // namespace Cassius
