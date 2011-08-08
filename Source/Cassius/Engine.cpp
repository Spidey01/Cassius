#include <Cassius/Engine.hpp>
#include <Cassius/SourceStream.hpp>
#include <Cassius/SourceFile.hpp>

#include <fstream>

namespace Cassius {

    void Engine::Call(const char *func, int nrets)
    {
        PushFunction(func, nrets, 0);
        Call();
    }

    void Engine::Evaluate(SourceFile &code)
    {
        std::ifstream f("Tests/test.lua");
        if (f.fail()) {
            // TODO handle errors
            return;
        }

        SourceStream ss(f);
        Evaluate(ss);
    }

    void Engine::PushFunction(const char *name)
    {
        PushFunction(name, 0, 0);
    }
}

