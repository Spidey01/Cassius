#ifndef CASSIUS_INCLUDE_BACKEND_HPP
#define CASSIUS_INCLUDE_BACKEND_HPP
// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <Cassius/Cassius.hpp>
#include <iosfwd>
#include <string>

class CxxPlugin;

namespace Cassius
{
    class Engine;

    /**
     * @brief Engine plugin handle.
     * 
     * Plugins are expected to:
     * 
     * - Be runtine loadable via dlopen() or platform equivalent.
     * 
     * - Implement one ScriptLanguage.
     * 
     * - Expose an extern "C" function called new_{name of plugin} that matches
     * the newengine_fptr_t.
     * 
     * - Expoe an extern "C" function called delete_{name of plugin} that
     * matches deleteengine_fptr_t.
     * 
     * @see Cassius::Manager, Cassius::Engine.
     */
    class CASSIUS_API Plugin
    {
      public:
        /** Function pointer for creating the Engine.
         */
        typedef Engine* (*newengine_fptr_t)();

        /** Function pointer for freeing the Engine.
         */
        typedef void (*deleteengine_fptr_t)(Engine*);

        /**
         * @brief Creates a Plugin.
         * 
         * @param name the base name of the plugin file to be loaded.
         * @param lang the script language this plugin supports.
         * @param logger the ostream to log messages to, or NULL for silence.
         */
        Plugin(const std::string& name, ScriptLanguages lang, std::ostream* logger);

        ~Plugin();

        // TODO: copy/assign or bust.

        /** @returns the plugin name.
         */
        const std::string name() const;

        /** @returns the script language.
         */
        ScriptLanguages scriptLanguage() const;

        /**
         * @brief Create a new instance of Engine.
         * 
         * @returns the Engine pointer on success; NULL on failure.
         */
        Engine* create();

        /**
         * @brief Destroy the instance of Engine.
         * 
         * @param engine a pointer returned from create().
         */
        void destroy(Engine* engine);

      private:
        std::string mName;
        ScriptLanguages mScriptLanguage;
        CxxPlugin* mPlugin;
        std::string mCreateName;
        newengine_fptr_t mCreateFunction;
        std::string mDestroyName;
        deleteengine_fptr_t mDestroyFunction;
    };

} // namespace Cassius

#endif // CASSIUS_INCLUDE_BACKEND_HPP