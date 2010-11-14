#ifndef CASSIUS_INCLUDE_SOURCE_HPP
#define CASSIUS_INCLUDE_SOURCE_HPP

#include <string>

#include "Cassius.hpp"

namespace Cassius {
    /** Abstract base class representing an executable chunk of Source code
     *
     */
    class CASSIUS_API Source {
      public:
        virtual ~Source() {};
        virtual std::string get() = 0;
    };
}

#endif
