#ifndef CASSIUS_INCLUDE_MANAGER_HPP
#define CASSIUS_INCLUDE_MANAGER_HPP
// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <Cassius/Cassius.hpp>
#include <map>
#include <set>
#include <string>

namespace Cassius
{
    class Engine;
    class Plugin;

    /** Simple class to help manage your active Engine objects.
     *
     * This is provided as a convenience class. It will mostly be of use when
     * you wish to have multiple execution contexts in the same application or
     * take your chances trying to embed several languages into the same
     * program.
     */
    class CASSIUS_API Manager
    {
      public:
        /**
        * @brief Construct a new Manager object
        * 
        * Unless NDEBUG has been defined this will assume std::clog can be used
        * for important logging.
        */
        Manager();

        /**
         * @brief Construct a new Manager object
         * 
         * @param logger used for important logging, such as dlopen() failures.
         * Set to NULL for silence.
         */
        Manager(std::ostream* logger);

        ~Manager();

        /**
         * @brief Creates an instance of Engine for embedding language.
         * 
         * Equivalent to calling createEngine(lang, "Default plugin name"); use
         * this unless implementing your own language plugins. See that
         * overrides documentation for further detail.
         * 
         * @param lang the desired script language.
         * @returns valid Engine* pointer on success, else NULL. Use destroyEngine() to free the pointer.
         * @throws runtime_error if things go sideways.
         */
        Engine* createEngine(ScriptLanguages lang);

        /**
         * @brief Creates an instance of Engine for embedding language using plugin.
         * 
         * Using this method allows overriding which plugin will be used for the
         * language.
         * 
         * This function will attempt to dynamically load the correct Engine
         * implementation for the specified language. Depending on your OS,
         * this may cause all sorts of stuff to happen. It is assumed that you
         * have read your systems manual, and that Cassius will do it's best
         * to return control to your program.
         *
         * No signal handlers or other means of trapping serious errors (e.g.
         * SIGSEGV) are installed. If your OS is known to react adversely to
         * such things as a failed dlopen() call, then please install the
         * appropriate handlers from *your* program.
         * 
         * @param lang the desired script language.
         * @param plugin the name of the plugin to be loaded.
         * @returns valid Engine* pointer on success, else NULL. Use destroyEngine() to free the pointer.
         * @throws runtime_error if things go sideways.
         * @see Cassius::Plugin;
         */
        Engine* createEngine(ScriptLanguages lang, const std::string& plugin);

        /**
         * @brief Destroy an Engine object.
         * 
         * After calling destroyEngine(): further use of the engine pointer and
         * any resources invoking it should be considered invalid, dangerous,
         * and highly at your own risk of crashing.
         * 
         * @param engine the pointer from createEngine().
         * @throws invalid_argument if engine is neither NULL nor remembered.
         */
        void destroyEngine(Engine* engine);

      private:
        std::ostream* mLogger;

        typedef std::set<Plugin*> PluginSet;
        PluginSet mPlugins;

        typedef std::map<Engine*, Plugin*> EngineToPluginMap;
        EngineToPluginMap mEngines;

        Manager(const Manager& other);
        const Manager& operator=(const Manager& other);
    };
} // namespace Cassius
#endif