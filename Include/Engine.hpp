#ifndef CASSIUS_INCLUDE_ENGINE_HPP
#define CASSIUS_INCLUDE_ENGINE_HPP

#include "Source.hpp"

namespace Cassius {
    class Engine {
      public:
        virtual ~Engine() {};
        virtual void Run(Source &code) = 0;
    };
}

#endif

