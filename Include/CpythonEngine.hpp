#ifndef CASSIUS_INCLUDE_CPYTHONENGINE_HPP
#define CASSIUS_INCLUDE_CPYTHONENGINE_HPP

#include "Engine.hpp"
#include "Source.hpp"

namespace Cassius {
    class CpythonEngine : public Engine {
      public:
        CpythonEngine();
        virtual ~CpythonEngine();
        virtual void Run(Source &code);

      private:
        CpythonEngine(const CpythonEngine &other);
        const CpythonEngine &operator=(const CpythonEngine &other);

    };
}

extern "C" Cassius::Engine *new_cpython(void);
extern "C" void delete_cpython(Cassius::Engine *obj);

#endif



