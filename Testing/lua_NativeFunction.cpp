// SPDX-License-Identifier: ISC
// Copyright 2022, Terry M. Poulin.

#include "./Common.hpp"

#include <Cassius/Engine.hpp>
#include <Cassius/Manager.hpp>
#include <Cassius/NativeFunction.hpp>
#include <Cassius/SourceString.hpp>

static int computed = 0;

static Cassius::NativeFunction::result_type cpp_function(Cassius::NativeFunction::argument_type args)
{
    cout << "cpp_function alled" << endl;
    Cassius::NativeFunction::result_type results;
    // for (size_t i=0; i < args.size(); ++i) {
    while (!args.empty()) {
        computed += args.top().as_integer();
        args.pop();
    }
    results.push(Cassius::Value(computed));
    return results;
}

void run_test(const char* name)
{
    Cassius::Manager manager;
    Cassius::Engine* engine = manager.createEngine(Cassius::LANG_LUA);
    if (!engine)
        throw TestFailure("Manager::createEngine() returned NULL");

    cout << "Registering function" << endl;
    Cassius::NativeFunction func("cpp_function", &cpp_function);
    engine->Register(func);

    string msg;

    Cassius::SourceString code("print(cpp_function(1,2,3,4,5))");
    cout << "Calling via Engine::Evalute() of code " << code.get() << endl;
    computed = 0;
    engine->Evaluate(code);
    cout << "computed = " << computed << endl;
    if (computed != 15) {
        msg.append("Unexpected result when called from Engine::Evaluate().");
    }

    cout << "Calling via C++ API" << endl;
    engine->PushFunction("cpp_function");
    engine->Push(1);
    engine->Push(2);
    engine->Push(3);
    engine->Push(4);
    engine->Push(5);
    computed = 0;
    Cassius::ValueList results = engine->Call();
    cout << "computed = " << computed << endl;
    if (results.top().as_integer() != computed) {
        msg.append("Unexpected result when called from C++ API.");
    }

    if (!msg.empty())
        throw TestFailure(msg);
    manager.destroyEngine(engine);
}
