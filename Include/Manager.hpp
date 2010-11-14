#ifndef CASSIUS_INCLUDE_MANAGER_HPP
#define CASSIUS_INCLUDE_MANAGER_HPP

#include <list>

#include "Cassius.hpp"
#include "Engine.hpp"

class CxxPlugin;

namespace Cassius {

    /** Simple class to help manage your active Engine objects.
     *
     * This is provided as a convenience class. It will mostly be of use when
     * you wish to have multiple execution contexts in the same application or
     * take your chances trying to embed several languages into the same
     * program.
     */
    class CASSIUS_API Manager {
      public:
        Manager();
        virtual ~Manager();

        /** Creates an instance of Engine for embedding language.
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
         * @param lang the language you wish to embed @param impl the backend
         * to use
         *
         * @returns a valid Engine object for lang, else NULL.
         * @throws std::runtime_error if unable to load backend.
         */
        virtual Engine *CreateEngine(ScriptLanguages lang, Backends
                                     impl=IMPL_DEFAULT);

      private:
        Manager(const Manager &other);
        const Manager &operator=(const Manager &other);

        std::list<Engine *> engines;

        typedef Engine *(*newengine_fptr_t)();
        typedef void (*deleteengine_fptr_t)(Engine *);
        struct {
            CxxPlugin *clua;
            newengine_fptr_t new_clua;
            deleteengine_fptr_t delete_clua;

            CxxPlugin *cpython;
            newengine_fptr_t new_cpython;
            deleteengine_fptr_t delete_cpython;
        } backends;
    };
}
#endif

