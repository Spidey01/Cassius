// SPDX-License-Identifier: ISC
// Copyright 2021, Terry M. Poulin.

#include "./Common.hpp"

#include <Cassius/Manager.hpp>
#include <Cassius/Engine.hpp>
#include <Cassius/SourceString.hpp>

void run_test(const char* name)
{
    Cassius::Manager manager;
    Cassius::Engine *engine = manager.createEngine(Cassius::LANG_LUA);
    if (!engine)
        throw TestFailure("Manager::createEngine() returned NULL");
    Cassius::SourceString code("2 + 2");
    engine->Evaluate(code);
    manager.destroyEngine(engine);
}
