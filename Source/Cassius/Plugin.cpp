// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <Cassius/Plugin.hpp>
#include <CxxPlugin.hxx>
#include <cassert>
#include <iostream>

namespace Cassius
{

    Plugin::Plugin(const std::string& name, ScriptLanguages lang, std::ostream* logger)
        : mName(name)
        , mScriptLanguage(lang)
        , mPlugin(NULL)
        , mCreateName("new_" + mName)
        , mCreateFunction(NULL)
        , mDestroyName("delete_" + mName)
        , mDestroyFunction(NULL)
    {
        // For now GIGO; no fancy name resolution.
        mPlugin = new CxxPlugin(name, logger);

        mCreateFunction = (newengine_fptr_t)mPlugin->load_funcptr(mCreateName.c_str());
        if (!mCreateFunction) {
            throw std::runtime_error("CxxPlugin::load_funcptr() failed for " + mCreateName);
        }

        mDestroyFunction = (deleteengine_fptr_t)mPlugin->load_funcptr(mDestroyName.c_str());
        if (!mDestroyFunction) {
            throw std::runtime_error("CxxPlugin::load_funcptr() failed for " + mDestroyName);
        }
    }

    Plugin::~Plugin()
    {
        if (mPlugin) {
            delete mPlugin;
        }
    }

    const std::string Plugin::name() const
    {
        return mName;
    }

    ScriptLanguages Plugin::scriptLanguage() const
    {
        return mScriptLanguage;
    }

    Engine* Plugin::create()
    {
        assert(mPlugin != NULL);
        assert(mCreateFunction != NULL);
        return mCreateFunction();
    }

    void Plugin::destroy(Engine* engine)
    {
        assert(mPlugin != NULL);
        assert(mDestroyFunction != NULL);
        return mDestroyFunction(engine);
    }

} // namespace Cassius
