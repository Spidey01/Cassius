#include "./Common.hpp"

#include <Cassius/Manager.hpp>
#include <Cassius/Engine.hpp>
#include <Cassius/SourceString.hpp>

void run_test(const char* name)
{
    Cassius::Manager manager;
    Cassius::Engine *engine = manager.CreateEngine(Cassius::LANG_PYTHON);
    Cassius::SourceString code("2 + 2");
    engine->Evaluate(code);
}
