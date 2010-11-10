
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
                backends.clua = new CxxPlugin("CassiusLuaEngine");
                backends.new_clua = (fptr_t)backends.clua->load_funcptr("new_clua");
                if (!backends.new_clua) {
                    return 0;
                }
            }
            return backends.new_clua();
            break;
          }

          default:
            return 0;
        }
    }

}

