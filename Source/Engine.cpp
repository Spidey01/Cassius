#include "../Include/Engine.hpp"

namespace Cassius {

    void Engine::Call(const char *func)
    {
        PushFunction(func);
        Call();
    }
}

