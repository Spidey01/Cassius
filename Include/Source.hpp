#ifndef CASSIUS_INCLUDE_SOURCE_HPP
#define CASSIUS_INCLUDE_SOURCE_HPP

#include <string>

namespace Cassius {
    /** Abstract base class representing an executable chunk of Source code
     *
     */
    class Source {
      public:
        virtual ~Source() {};
        virtual const std::string get() = 0;
    };
}

#endif
