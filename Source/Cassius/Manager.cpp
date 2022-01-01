// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <Cassius/Manager.hpp>
#include <Cassius/Plugin.hpp>
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

using std::invalid_argument;
using std::runtime_error;
using std::string;
using std::stringstream;

namespace Cassius
{

    Manager::Manager()
#if defined(NDEBUG)
        : mLogger(NULL)
#else
        : mLogger(&std::clog)
#endif
        , mPlugins()
        , mEngines()
    {
    }

    Manager::Manager(std::ostream* logger)
        : mLogger(logger)
        , mPlugins()
        , mEngines()
    {
    }

    Manager::~Manager()
    {
        // Cheesy horror or brillant reuse?
        while (!mEngines.empty()) {
            destroyEngine(mEngines.begin()->first);
        }
    }

    Engine* Manager::createEngine(ScriptLanguages lang)
    {
        string plugin;
        switch (lang) {
            case LANG_LUA:
                plugin = "CassiusCluaEngine";
                break;
            case LANG_PYTHON:
                plugin = "CassiusCpythonEngine";
                break;
            default:
                break;
        }
        return createEngine(lang, plugin);
    }

    Engine* Manager::createEngine(ScriptLanguages lang, const string& plugin)
    {
        /*
         * XXX: This assumes that it is safe to create and destroy an instance
         * of the plugin for each instance.
         *
         * For POSIX dlopen() and Windows LoadLibrary() platforms this is true.
         * Because these platforms use per process reference counting and try to
         * do the right thing. Any sane platform should do this if it has a
         * concept of runtime library loading.
         * 
         * At worst we should waste a handful of extra bytes per engine by using
         * one Plugin per Engine instead of reusing Plugin instances for each
         * Engine associated with that module.
         */
        Plugin* p = new Plugin(plugin, lang, mLogger);

        if (!mPlugins.insert(p).second) {
            delete p;
            stringstream err;
            err << "Cassius::Manager::createEngine(): mPlugins.insert() failed for 0x" << std::hex << p << " plugin for " << plugin;
            throw runtime_error(err.str());
        }

        Engine* engine = NULL;
        try {
            engine = p->create();
        } catch (std::exception& ex) {
            string msg("Cassius::Manager::createEngine(): extern C functions should never throw but plugin's create function threw exception: ");
            msg.append(ex.what());
            throw runtime_error(msg);
        }

        if (engine) {
            /* For destroyEngine(). */
            mEngines[engine] = p;
        }

        return engine;
    }

    void Manager::destroyEngine(Engine* engine)
    {
        if (!engine) {
            if (mLogger)
                *mLogger << "Cassius::Manager::destroyEngine(): called with NULL." << std::endl;
            return;
        }

        EngineToPluginMap::iterator it = mEngines.find(engine);
        if (it == mEngines.end()) {
            stringstream err;
            err << "Cassius::Manager::destroyEngine(): engine pointer " << engine << " is not in mEngines.";
            throw invalid_argument(err.str());
        }

        assert(engine == it->first);
        Plugin* p = it->second;

        mEngines.erase(it);
        /** See XXX comment in createEngine(). */
        mPlugins.erase(p);
        p->destroy(engine);
        delete p;
    }

} // namespace Cassius
