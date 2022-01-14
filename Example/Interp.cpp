#include "./Interp.hpp"

#include <Cassius/Engine.hpp>
#include <Cassius/Manager.hpp>
#include <Cassius/SourceString.hpp>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

using std::endl;
using std::istream;
using std::logic_error;
using std::ostream;
using std::runtime_error;
using std::string;

static bool notSpace(int ch);
static string trim(const string& input);

static bool notSpace(int ch)
{
    return !std::isspace(ch);
}

static string trim(const string& input)
{
    string copy = input;

    copy.erase(copy.begin(),
               std::find_if(copy.begin(), copy.end(), &notSpace));
    copy.erase(std::find_if(copy.rbegin(), copy.rend(), &notSpace).base(),
               copy.end());

    return copy;
}

namespace Example
{
    Interp::Interp(std::istream& input, std::ostream& output, std::ostream& error)
        : mIn(input)
        , mOut(output)
        , mErr(error)
        , mDebug(false)
        , mManager(&mErr)
        , mEngine(NULL)
        , mLength(0)
        , mBuffer()
    {
    }

    void Interp::help()
    {
        if (mEngine) {
            // TODO
        } else {
            mOut
                << "Cassius Example Interpreter" << endl
                << endl
                << "Commands:" << endl
                << endl
                << "- help      Show this help message." << endl
                << "- debug     Toggle debug output." << endl
                << "- exit      Exit program." << endl
                << "- quit      Quit program." << endl
                << "- lua       Enter Lua script." << endl
                << endl;
        }
    }

    int Interp::loop()
    {
        int rc = EXIT_SUCCESS;

        string line;
        while (mIn) {
            prompt(line);
            eval(line);
        }

        return rc;
    }

    void Interp::prompt(std::string& line)
    {
        if (mLength)
            mOut << "+";
        if (mEngine) {
            switch (mEngine->lang()) {
                case Cassius::LANG_LUA:
                    mOut << "CassiusCluaEngine";
                    break;
                default:
                    throw logic_error("Interp::prompt(): switch/case out of date");
            }
        } else {
            mOut << "Cassius";
        }
        mOut << "> ";
        std::getline(mIn, line);
    }

    void Interp::eval(const std::string& code)
    {
        if (mDebug)
            mOut << "eval(): mLength: " << mLength << " mBuffer.str(): " << mBuffer.str() << endl;

        if (mEngine) {
            //
            // Empty line triggers evaluation of the buffer. Otherwise we buffer
            // input so that multiples lines of code can be evaluated.
            //

            if (!code.empty()) {
                mLength += code.size();
                mBuffer << code << endl;
                return;
            }

            // TODO: fix SourceStream.
            Cassius::SourceString source(mBuffer.str());
            mBuffer.str("");
            mLength = 0;

            mEngine->Evaluate(source);
        } else {
            //
            // Internal commands.
            //

            string line = trim(code);
            if (line == "help") {
                help();
            } else if (line == "debug") {
                mDebug = !mDebug;
                mOut << "Debug mode " << (mDebug ? "on" : "off") << endl;
            } else if (line == "exit" || line == "quit") {
                mOut << "Goodbye." << endl;
                std::exit(0);
            } else if (line == "lua") {
                lang(Cassius::LANG_LUA);
            } else {
                mErr << "Unknown command: " << '"' << line << '"' << endl;
            }
        }
    }

    void Interp::lang(Cassius::ScriptLanguages which)
    {
        if (mEngine) {
            mOut << "Destroying current engine" << endl;
            mManager.destroyEngine(mEngine);
        }

        string name;
        switch (which) {
            case Cassius::LANG_LUA:
                name = "Lua";
                break;
            default:
                throw std::invalid_argument("Interp::lang(): that one is still TODO");
                break;
        }
        mOut << "Creating engine for " << name;

        try {
            mEngine = mManager.createEngine(which);
        } catch (runtime_error& ex) {
            mErr << "Failed to load engine for " << name << endl;
            mEngine = NULL;
        }

        mOut << "Enter code. Use a blank line to trigger evaluation." << endl;
    }
}; // namespace Example
