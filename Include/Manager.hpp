#ifndef CASSIUS_INCLUDE_MANAGER_HPP
#define CASSIUS_INCLUDE_MANAGER_HPP

#include "Engine.hpp"

namespace Cassius {

    /** Simple class to help manage your active Engine objects.
     *
     * This is provided as a convenience class. It will mostly be of use when
     * you wish to have multiple execution contexts in the same application or
     * take your chances trying to embed several languages into the same
     * program.
     */
    class Manager {
      public:
        Manager();
        virtual ~Manager();

      private:
        Manager(const Manager &other);
        const Manager &operator=(const Manager &other);
    };
}
#endif

