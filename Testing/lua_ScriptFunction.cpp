// SPDX-License-Identifier: ISC
// Copyright 2022, Terry M. Poulin.

#include "./Common.hpp"

#include <Cassius/Engine.hpp>
#include <Cassius/Manager.hpp>
#include <Cassius/ScriptFunction.hpp>
#include <Cassius/SourceStream.hpp>
#include <Cassius/SourceString.hpp>

void run_test(const char* name)
{
    Cassius::Manager manager;
    Cassius::Engine* engine = manager.createEngine(Cassius::LANG_LUA);
    if (!engine)
        throw TestFailure("Manager::createEngine() returned NULL");

    std::stringstream code;
    code
        << "-- A simple function" << std::endl
        << "function from_script(a, b)" << std::endl
        << '\t' << "print(\"Lua from_script() called with args\")" << std::endl
        << '\t' << "return a + b" << std::endl
        << "end" << std::endl;

    // XXX: Causes nil instead of _G["from_script"] to be pushed?!?
    // Cassius::SourceStream source(code);
    Cassius::SourceString source(code.str());

    std::cout << "Evaluating code: " << std::endl
              << source.get() << std::endl;
    engine->Evaluate(source);
    std::cout << "Calling from C++ by Engine::Evaluate()." << std::endl;
    Cassius::SourceString print_and_run("print(\"return value:\", from_script(2, 2))");
    engine->Evaluate(print_and_run);

    std::cout << "Wrapping in ScriptFunction" << std::endl;
    using from_script_signature = Cassius::ScriptFunction<int(int, int)>;
    from_script_signature from_script = Cassius::make_scriptfunction<int, int, int>(engine, "from_script");

    std::cout << "Calling from_script() from C++" << std::endl;
    int r = from_script(4, 4);
    std::cout << "return value: " << r << std::endl;
    if (r != 4 + 4)
        throw TestFailure("from_script() gave bad return value");

    manager.destroyEngine(engine);
}
