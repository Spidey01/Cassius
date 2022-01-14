#ifndef CASSIUS_EXAMPLE_INTERP_HPP
#define CASSIUS_EXAMPLE_INTERP_HPP

#include <Cassius/Manager.hpp>
#include <iosfwd>
#include <string>
#include <sstream>

namespace Example
{
    /**
     * @brief Cassius Example Interpreter.
     * 
     * Implements a basic Read Eval Print Loop (REPL) that can change between
     * its own commands and running script engines.
     */
    class Interp
    {
      public:
        /**
         * @brief Construct a new Interp object
         * 
         * @param input the standard input stream, e.g. std::cin.
         * @param output the standard output stream, e.g. std::cout.
         * @param error the standard error stream, e.g. std::cerr or std::clog.
         */
        Interp(std::istream& input, std::ostream& output, std::ostream& error);

        /**
         * @brief Print help.
         * 
         */
        void help();

        /**
         * @brief Execute the REPL.
         * 
         * @return int return code for main().
         */
        int loop();

        /**
         * @brief Prompt for input.
         * 
         * @param[out] line empty string or a chunk of input.
         */
        void prompt(std::string& line);

        /**
         * @brief Evaluate some code.
         * 
         * @param code next line to append to the code buffer. An empty line
         * triggers evaluation of the buffer.
         */
        void eval(const std::string& code);

        /**
         * @brief Loads a scripting language.
         * 
         * @param which the language to load.
         */
        void lang(Cassius::ScriptLanguages which);

      private:
        std::istream& mIn;
        std::ostream& mOut;
        std::ostream& mErr;
        bool mDebug;
        Cassius::Manager mManager;
        Cassius::Engine* mEngine;
        std::streamsize mLength;
        std::stringstream mBuffer;
    };

} // namespace Example
#endif // CASSIUS_EXAMPLE_INTERP_HPP