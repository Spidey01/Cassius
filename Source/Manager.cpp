
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
        switch (lang) {
            case LANG_LUA:
                {
                    if (!backends.clua) {
                        backends.clua = new CxxPlugin("CassiusCluaEngine");
                        backends.new_clua = (fptr_t)backends.clua->load_funcptr("new_clua");
                        if (!backends.new_clua) {
                            return 0;
                        }
                    }
                    return backends.new_clua();
                    break;
                }
            case LANG_PYTHON:
                {
                    if (!backends.cpython) {
                        backends.cpython = new CxxPlugin("CassiusCpythonEngine");
                        backends.new_cpython = (fptr_t)backends.cpython->load_funcptr("new_cpython");
                        if (!backends.new_cpython) {
                            return 0;
                        }
                    }
                    return backends.new_cpython();
                    break;
                }
            default:
                return 0;
        }
    }

}

